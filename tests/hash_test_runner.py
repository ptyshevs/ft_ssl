import argparse
import subprocess
import random
import string
import sys
import multiprocessing as mp
from hash_unit_tests import *

BLACK = '\033[0;30m'
RED = '\033[0;31m'
GREEN = '\033[0;32m'
BROWN = '\033[0;33m'
BLUE = '\033[0;34m'
PURPLE = '\033[0;35m'
CYAN = '\033[0;36m'
LGRAY = '\033[0;37m'
DGRAY = '\033[1;30m'
LRED = '\033[1;31m'
LGREEN = '\033[1;32m'
YELLOW = '\033[1;33m'
LBLUE = '\033[1;34m'
PINK = '\033[1;35m'
LCYAN = '\033[1;36m'
WHITE = '\033[1;37m'
NC = '\033[0m'

def run_command(command):
    try:
        out = subprocess.check_output(command, shell=True)
        return str(out, encoding='utf-8')
    except subprocess.CalledProcessError as e:
        print(str(e.output, encoding='utf-8'))
        return None

alphabet = string.ascii_letters + string.digits

def gen_rand_string(maxlen=10):
    return ''.join(random.choices(alphabet, k=maxlen))


def fuzz(ft_ssl_path, subcommand, ssl_binary="openssl", n=100, l=10, verbose=0):
    fuzz_suite = [(f'fuzz{i}', gen_rand_string(maxlen=l)) for i in range(n)]

    pool_input = [(ft_ssl_path, subcommand, ssl_binary, verbose, test_name, test_input) \
                  for (test_name, test_input) in fuzz_suite]

    errors = pool.starmap(job, pool_input)
    errors = [e for e in errors if len(e)]

    if not verbose:
            print("")  # finish line
    return errors

def output_errors(error_log, file=sys.stdout):
    """
    Error format - tuple of (gt_input, gt_output, my_input, my_output)
    """
    for (gt_in, gt_out, my_in, my_out) in error_log:
        print("[openssl in]:{}\n[openssl_out]: {}\n[ft_ssl in]:{}\n[ft_ssl out]: {}".format(gt_in, gt_out, my_in, my_out), file=file)

def subcommand_to_unit_tests(subcommand):
    if subcommand == 'sha256':
        return sha256_test_suite()
    else:
        return None

def job(ft_ssl_path, subcommand, ssl_binary, verbose, test_name, test_input):
    command_template = "echo -n '{}' | {} " + subcommand

    my_command = command_template.format(test_input, ft_ssl_path)
    gt_command = command_template.format(test_input, ssl_binary)

    gt_out = run_command(gt_command)
    my_out = run_command(my_command)

    same_result = gt_out == my_out
    if same_result:
        out = tuple()
    else:
        out = (gt_command, gt_out, my_command, my_out)

    if verbose == 1 and not same_result:
        print("[gt] {} != {} [ft]".format(gt_out, my_out))
    else:
        print("{}.{}".format(GREEN if same_result else RED, NC), end='', flush=True)

    return out

def run_ut_suite(ft_ssl_path, subcommand, test_suite, pool, ssl_binary="openssl", verbose=False):
    errors = []
    command_template = "echo -n '{}' | {} " + subcommand

    pool_input = [(ft_ssl_path, subcommand, ssl_binary, verbose, test_name, test_input) \
            for (test_name, test_input) in test_suite]

    errors = pool.starmap(job, pool_input)
    errors = [e for e in errors if len(e)]

    if not verbose:
        print("")  # finish line
    return errors


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("-p", "--path", default="./ft_ssl", help="path to ft_ssl executable")
    parser.add_argument('-f', '--fuzz', default=False, help="Apply fuzzing after unit-tests are run", action='store_true')
    parser.add_argument("-v", '--verbose', default=False, help="Be more verbose", action='store_true')
    parser.add_argument("-l", '--log', default='error.log', help='File to write diff into')
    parser.add_argument("-j", "--jobs", default=4, help='Number of workers in a thread pool')

    args = parser.parse_args()

    if type(args.jobs) is not int:
        args.jobs = int(args.jobs)

    pool = mp.Pool(args.jobs)

    subcommand = 'sha256'

    error_log = []
    # for subcommand in ['sha256', 'sha512']

    # part 1: unit-tests

    test_suite = subcommand_to_unit_tests(subcommand)
    if test_suite is None:
        print("ERROR: subcommand {} is not recognized".format(subcommand))
        exit(1)
    
    ut_errors = run_ut_suite(args.path, subcommand, test_suite, pool, verbose=args.verbose)
    error_log.extend(ut_errors)
    
    # part 2: optional fuzzing

    if args.fuzz:
        for l in [10, 100, 1000]:
            print("Fuzzing {} with len={}".format(subcommand, l))
            fuzz_errors = fuzz(args.path, subcommand, verbose=args.verbose, l=l)
            error_log.extend(fuzz_errors)
    
    if len(error_log) > 0:
        with open(args.log, 'w+') as f:
            output_errors(error_log, f)
            print("Errors written into", args.log)