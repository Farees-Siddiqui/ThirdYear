import math

# write a function that takes in a string representing a boolean operation. for example A and B or A or B
# the function should print the truth table for the operation

def eval_operation(operations, values):
    # create a list of the operations
    operations_list = []
    for op in operations:
        if op == "and" or op == "or" or op == "not" or op == "xor":
            operations_list.append(op)
        else:
            operations_list.append(values[op])
    # evaluate the operations
    while len(operations_list) > 1:
        # evaluate not
        for i in range(len(operations_list)):
            if operations_list[i] == "not":
                operations_list[i] = not operations_list[i+1]
                del operations_list[i+1]
                break
        # evaluate xor
        for i in range(len(operations_list)):
            if operations_list[i] == "xor":
                operations_list[i] = operations_list[i-1] ^ operations_list[i+1]
                del operations_list[i-1]
                del operations_list[i]
                break
        # evaluate and
        for i in range(len(operations_list)):
            if operations_list[i] == "and":
                operations_list[i] = operations_list[i-1] and operations_list[i+1]
                del operations_list[i-1]
                del operations_list[i]
                break
        # evaluate or
        for i in range(len(operations_list)):
            if operations_list[i] == "or":
                operations_list[i] = operations_list[i-1] or operations_list[i+1]
                del operations_list[i-1]
                del operations_list[i]
                break
    return operations_list[0]

def gen_truth_table(operation):
    # split the operation into a list of the individual operations
    operations = operation.split(" ")
    # create a list of the variables
    variables = []
    for op in operations:
        if op != "and" and op != "or" and op != "not" and op != "xor":
            variables.append(op)
    # remove duplicates
    variables = list(set(variables))
    # sort the variables
    variables.sort()
    # create a list of all possible combinations of the variables
    combinations = []
    for i in range(2**len(variables)):
        combinations.append([])
        for j in range(len(variables)):
            combinations[i].append((i // 2**j) % 2)
    # create a dictionary of the variables and their values
    values = {}
    for i in range(len(variables)):
        values[variables[i]] = combinations[0][i]
    # create a list of the values of the operations
    operation_values = []
    for combination in combinations:
        for i in range(len(variables)):
            values[variables[i]] = combination[i]
        operation_values.append(eval_operation(operations, values))
    # print the truth table
    print("Truth Table for " + operation)
    print(" ".join(variables) + " " + operation)
    for i in range(len(combinations)):
        print(" ".join([str(x) for x in combinations[i]]) + " " + str(operation_values[i]))
        
gen_truth_table("A and not B or A and not C or B and C")