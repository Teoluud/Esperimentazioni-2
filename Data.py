class Data:
    def __init__(self) -> None:
        self.data_x: list = []
        self.data_y: list = []
        self.err_x: list = []
        self.err_y: list = []
        self.n_points: int = 0
    
    def import_from_file(self, file_path: str, default_err_x: float = -99, default_err_y: float = -99) -> None:
        n_data_x: float = 0
        n_data_y: float = 0
        n_err_x: float = default_err_x
        n_err_y: float = default_err_y

        with open(file_path, "r") as file:
            for line in file:
                line = line.strip("\n")
                line_list = line.split()
                n_data_x = float(line_list[0])
                match default_err_x:
                    case -99:
                        n_err_x = float(line_list[1])
                        n_data_y = float(line_list[2])
                        if default_err_y == -99:
                            n_err_y = float(line_list[3])
                    case _:
                        n_data_y = float(line_list[1])
                        if default_err_y == -99:
                            n_err_y = float(line_list[2])
                self.data_x.append(n_data_x)
                self.err_x.append(n_err_x)
                self.data_y.append(n_data_y)
                self.err_y.append(n_err_y)
                self.n_points += 1
        return

if __name__ == "__main__":
    data = Data()
    data.import_from_file('prova.txt', 0)