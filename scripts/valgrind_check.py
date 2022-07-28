from sre_constants import FAILURE, SUCCESS
import sys
import argparse

LEAK_SUMMARY        = ("LEAK SUMMARY")
ERROR_SUMMARY       = ("ERROR SUMMARY")
NUMBER_ERROR_INDEX  = (3)
NO_ERROR_CODE       = (0)

def memory_error_summary_info(data_line):
    split_data_line = data_line.split(' ')
    number_error = int(split_data_line[NUMBER_ERROR_INDEX])
    if number_error != NO_ERROR_CODE:
        return True
    return False

def is_memory_error_summary(data_line):
    if ERROR_SUMMARY in data_line:
        return True
    return False

def is_memory_leak_summary(data_line):
    if LEAK_SUMMARY in data_line:
        return True
    return False

def manage_data_file(data):
    list_data_line = data.split('\n')
    for data_line in list_data_line:
        if is_memory_leak_summary(data_line) == True:
            return FAILURE
        if is_memory_error_summary(data_line) == True:
            if memory_error_summary_info(data_line) == True:
                return FAILURE
    return SUCCESS

if "__main__" == __name__:
    parser = argparse.ArgumentParser()
    parser.add_argument("infile", type=argparse.FileType('r'), default=sys.stdin,
                help="Input file, must be a valgrind output file that need to be parsed to check for any LEAK ERROR.")
    args = parser.parse_args()
    data = args.infile.read()
    return_from_function = manage_data_file(data)
    exit(True) if return_from_function == FAILURE else exit(False)
