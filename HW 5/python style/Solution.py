from collections import defaultdict, deque
from copy import deepcopy
from dataclasses import dataclass


@dataclass(frozen=True, order=True)
class Edge:
    id_k: str = ""
    id_l: str = ""
    edge_length: int = 0


class Solution:
    def __init__(self) -> None:
        # self.__node_number: int = 0
        self.__event_number: int = 0
        self.__adj_list = defaultdict(list)
        self.__adj_list_inv = defaultdict(list)

        self.__in_degree = defaultdict(int)
        self.__in_degree_inv = defaultdict(int)

        self.__data_events: list[Edge] = []
        self.__critical_path: list[Edge] = []

        self.__edge_table = defaultdict(int)

    @staticmethod
    def __topological_sort(
        adj_list_map: defaultdict, in_degree: defaultdict
    ) -> list[int]:
        """
        A topological sort algorithm.

        :param adj_list_map: defaultdict
        :type adj_list_map: defaultdict
        :param in_degree: a dictionary that maps a node to its in-degree
        :type in_degree: defaultdict
        :return: A list of integers.
        """
        in_degree_cpy = deepcopy(in_degree)
        res = []
        pq = deque([index for index, degree in in_degree_cpy.items() if degree == 0])

        while pq:
            res.append(pq.popleft())

            for node in adj_list_map[res[-1]]:
                in_degree_cpy[node] -= 1
                if in_degree_cpy[node] == 0:
                    pq.append(node)

        return res

    @staticmethod
    def __early_latest_time_func(
        topological_list: list[int],
        adj_list: defaultdict,
        edge_table: defaultdict,
        max_min_func,
        func,
        result_init_number: int = 0,
    ) -> dict:
        """
        It takes a graph, a function, and a starting value, and returns a dictionary of the results of
        applying the function to the graph

        :param topological_list: list[int]
        :type topological_list: list[int]
        :param adj_list: defaultdict
        :type adj_list: defaultdict
        :param edge_table: defaultdict
        :type edge_table: defaultdict
        :param max_min_func: max or min function
        :param func: the function to apply to the edge weight and the result of the previous node
        :param result_init_number: int = 0, defaults to 0
        :type result_init_number: int (optional)
        :return: A dictionary of the earliest and latest times for each node.
        """
        result_map = {k: result_init_number for k in topological_list}

        for pop_item in topological_list:
            for item in adj_list[pop_item]:
                result_map[item] = max_min_func(
                    result_map[item],
                    func(result_map[pop_item], edge_table[frozenset((pop_item, item))]),
                )

        return result_map

    def __make_critical_path_str(self) -> list[list[str]]:
        res: list[list[str]] = []

        for item_edge in self.__critical_path:
            is_find_it = False
            res_now_size = len(res)

            for i in range(res_now_size):
                if res[i][-1] == item_edge.id_k:
                    res[i].append(item_edge.id_l)
                    is_find_it = True
                    continue

                if item_edge.id_k in res[i]:
                    find_index = res[i].index(item_edge.id_k)
                    res.append(deepcopy(res[i][: find_index + 1]) + [item_edge.id_l])
                    is_find_it = True

            if is_find_it is False:
                res.append([item_edge.id_k, item_edge.id_l])

        return res

    def read_file(self, file_name_in: str) -> None:

        data_in = ""

        with open(file=file_name_in, mode="r") as file_open:
            data_in = file_open.readlines()

        data_in = [i.strip().split(" ") for i in data_in]

        for value_list in data_in:
            length = int(value_list.pop(-1))
            idk, idl = value_list

            self.__adj_list[idk].append(idl)
            self.__adj_list_inv[idl].append(idk)

            self.__edge_table[frozenset(value_list[:2])] = length

            self.__in_degree.setdefault(idk, 0)
            self.__in_degree_inv.setdefault(idl, 0)

            self.__in_degree[idl] += 1
            self.__in_degree_inv[idk] += 1

            self.__data_events.append(Edge(id_k=idk, id_l=idl, edge_length=length))

        self.__event_number = len(self.__data_events)

    def run_solution(self, file_name_out: str) -> None:
        topological_sort_list = Solution.__topological_sort(
            adj_list_map=self.__adj_list, in_degree=self.__in_degree
        )

        topological_sort_list_inv = Solution.__topological_sort(
            adj_list_map=self.__adj_list_inv, in_degree=self.__in_degree_inv
        )

        ee_map = Solution.__early_latest_time_func(
            topological_list=topological_sort_list,
            adj_list=self.__adj_list,
            edge_table=self.__edge_table,
            max_min_func=lambda a, b: max(a, b),
            func=lambda a, b: a + b,
            result_init_number=0,
        )

        node_max_value = max(ee_map.values())

        le_map = Solution.__early_latest_time_func(
            topological_list=topological_sort_list_inv,
            adj_list=self.__adj_list_inv,
            edge_table=self.__edge_table,
            max_min_func=lambda a, b: min(a, b),
            func=lambda a, b: a - b,
            result_init_number=node_max_value,
        )

        to_file_string = []

        for data_event in self.__data_events:
            ee_part, le_part = (
                ee_map[data_event.id_k],
                le_map[data_event.id_l] - data_event.edge_length,
            )

            y_n = "Y" if ee_part == le_part else "N"
            output_string = f"{data_event.id_k} {data_event.id_l} {ee_part} {le_part} {le_part-ee_part} {y_n}"

            to_file_string.append(output_string)
            if ee_part == le_part:
                self.__critical_path.append(data_event)

        to_file_string.append(f"max latency: {node_max_value}")

        res_make_path = self.__make_critical_path_str()
        show_path = [" ".join(i) for i in res_make_path]

        to_file_string.extend(["critical paths:"] + show_path)

        with open(file=file_name_out, mode='w') as file_out:
            file_out.write("\n".join(to_file_string))
