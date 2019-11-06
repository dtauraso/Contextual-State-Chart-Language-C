def makeIndents(indents):

    indent_string = ""
    while indents > 0:
        indent_string += " "
        indents -= 1
    return indent_string

def backTrack(tracker, graph):
    name_collected = ""
    # prev = tracker
    # base case has already been handled
    while True:
        # 2 cases of overshooting
        if graph[tracker]["end_of_word"]:
            # prev will equal tracker if true the first time
            return name_collected
        if graph[tracker]["parent"] == -1:
            return name_collected
        name_collected = graph[tracker]["name"] + name_collected
        # prev = tracker
        tracker = graph[tracker]["parent"]
    
def printTrieTree(graph):

    indents = 0
    ith_edge_stack = []

    # 	ith edge of the node before root is 0
    ith_edge_stack.append(0)
    current_node_id = 0
    i = 0
    current_node_id = graph[current_node_id]["children"][ ith_edge_stack[len(ith_edge_stack) - 1] ]

    while len(ith_edge_stack) > 0:
        print("i", i)
        # print(graph[current_node_id]["children"], ith_edge_stack[len(ith_edge_stack) - 1])
        print("node", current_node_id)
        # process string node is at the end of
        if graph[current_node_id]["end_of_word"]:
            print("at end of word node is", current_node_id)
            # traverse backwards and collect chars in reverse order(top at previous end_of_word)
            tracker = graph[current_node_id]["parent"]
            if graph[tracker]["end_of_word"]:
                print(makeIndents(indents) + graph[tracker]["name"])
            else:
                print("long name")
                name_collected = backTrack(tracker, graph)
                print(makeIndents(indents) + name_collected + str(graph[current_node_id]["name"]))
            indents += 3
            
        if len(graph[current_node_id]["children"]) > 0:
            # print("here")
            ith_edge_stack.append(0)
            # print(graph[current_node_id]["children"], ith_edge_stack[len(ith_edge_stack) - 1])
            # print()
            current_node_id = graph[current_node_id]["children"][ ith_edge_stack[len(ith_edge_stack) - 1] ]
            # print("new node", current_node_id)
        else:
            last_edge = ith_edge_stack[len(ith_edge_stack) - 1]
            # print(ith_edge_stack, indents, graph[current_node_id]["parent"],
            # graph[  graph[current_node_id]["parent"] ]["children"])
            while len(ith_edge_stack) > 0 and last_edge >= len(graph[  graph[current_node_id]["parent"] ]["children"]) - 1:
                if graph[current_node_id]["end_of_word"]:
                    indents -= 3

                current_node_id = graph[current_node_id]["parent"]
                if len(ith_edge_stack) > 0:

                    del ith_edge_stack[len(ith_edge_stack) - 1]
                    # print(ith_edge_stack)
                    if len(ith_edge_stack) > 0:

                        last_edge = ith_edge_stack[len(ith_edge_stack) - 1]
            if ith_edge_stack == []:
                break;
            current_node_id = graph[current_node_id]["parent"]

            print(ith_edge_stack, indents)

            ith_edge_stack[len(ith_edge_stack) - 1] += 1
            print(ith_edge_stack, indents, current_node_id)

            current_node_id = graph[current_node_id]["children"][ ith_edge_stack[len(ith_edge_stack) - 1] ]
        i += 1
        print()
        print()
            

# print("works")

# a_count
# b_count
# c_count
# input_string
# i
# idea works but missing vital parts
trie_tree = [

    {"name": "root", "children": [1, 8, 15, 22], "parent": -1, "end_of_word": 0},

    {"name": "a", "children": [2], "parent": 0, "end_of_word": 0},
    {"name": "_", "children": [3], "parent": 1, "end_of_word": 0},
    {"name": "c", "children": [4], "parent": 2, "end_of_word": 0},
    {"name": "o", "children": [5], "parent": 3, "end_of_word": 0},
    {"name": "u", "children": [6], "parent": 4, "end_of_word": 0},
    {"name": "n", "children": [7], "parent": 5, "end_of_word": 0},
    {"name": "t", "children": [], "parent": 6, "end_of_word": [1, 7]}, # 7

    {"name": "b", "children": [9], "parent": 0, "end_of_word": 0},
    {"name": "_", "children": [10], "parent": 8, "end_of_word": 0},
    {"name": "c", "children": [11], "parent": 9, "end_of_word": 0},
    {"name": "o", "children": [12], "parent": 10, "end_of_word": 0},
    {"name": "u", "children": [13], "parent": 11, "end_of_word": 0},
    {"name": "n", "children": [14], "parent": 12, "end_of_word": 0},
    {"name": "t", "children": [], "parent": 13, "end_of_word": [8, 14]}, # 14

    {"name": "c", "children": [16], "parent": 0, "end_of_word": 0},
    {"name": "_", "children": [17], "parent": 15, "end_of_word": 0},
    {"name": "c", "children": [18], "parent": 16, "end_of_word": 0},
    {"name": "o", "children": [19], "parent": 17, "end_of_word": 0},
    {"name": "u", "children": [20], "parent": 18, "end_of_word": 0},
    {"name": "n", "children": [21], "parent": 19, "end_of_word": 0},
    {"name": "t", "children": [], "parent": 20, "end_of_word": [15, 21]}, #21


    {"name": "i", "children": [23], "parent": 0, "end_of_word": [22],        "paths": [1, 2], "pivot": True},
    {"name": "n", "children": [24], "parent": 22, "end_of_word": 0,          "paths": [2], "pivot": True},
    {"name": "p", "children": [25], "parent": 23, "end_of_word": [23, 24],   "paths": [2], "pivot": False},
    {"name": "u", "children": [26], "parent": 24, "end_of_word": 0,          "paths": [1], "pivot": False},
    {"name": "t", "children": [27], "parent": 25, "end_of_word": 0,          "paths": [1], "pivot": False},
    {"name": "s", "children": [28], "parent": 26, "end_of_word": 0,          "paths": [1], "pivot": False},
    {"name": "t", "children": [29], "parent": 27, "end_of_word": 0,          "paths": [1], "pivot": False}, #28
    {"name": "r", "children": [30], "parent": 28, "end_of_word": 0,          "paths": [1], "pivot": False},
    {"name": "i", "children": [31], "parent": 29, "end_of_word": 0,          "paths": [1], "pivot": False},
    {"name": "n", "children": [32], "parent": 30, "end_of_word": 0,          "paths": [1], "pivot": False},
    {"name": "g", "children": [], "parent": 31, "end_of_word": [22, 32],     "paths": [1], "pivot": False}, # 32


]
'''
is it a pivot?
    if yes, then what paths can we start from here?
        if we have paths then indent
    if no, are we at the end of a word?

yes, [1, 2] so indent
yes, [2] so indent
no, node 24 so back out to begining of word and decrease indent

'''
# if start of word being printed has a pivot of true
    # how to prove it has already been indented
    # print and indent

# i
#   np
# input_string
# print(trie_tree)
printTrieTree(trie_tree)