import random
import unittest

from validator import ValidationError
from texttable import Texttable


class ComputerBoard:
    def __init__(self, width, height):
        self._cols = width
        self._rows = height
        self._data = [[0] * self._cols for i in range(self._rows)]
        self._computer_cabin_list = []
        self._computer_plane_list = []
        self._validation = ValidationError()

    def generate_planes(self):
        """
        We generate the three planes of the computer
        :return: None
        """
        i = 0
        while i < 3:
            try:
                x = random.randint(0, 9)
                y = random.randint(0, 9)
                orientation = random.choice(["N", "S", "E", "W"])
                self._validation.validate_plane(y, x, orientation, self._computer_plane_list)
                self._computer_cabin_list.append([x, y])
                i = i + 1
            except Exception:
                pass

    def move(self, x, y):
        """
        :param x: the row that the player has selected
        :param y:  the column that the player has selected
        :return: The symbol to know the effect of this coord on the computer's table
        """
        try:
            self._validation.valid_move(x, y)
            x = int(x)
            y = int(y)
            for cab in self._computer_cabin_list:
                if int(cab[0]) == x and int(cab[1]) == y:
                    self._data[x][y] = "C"
                    return self._data[x][y]

            for coord in self._computer_plane_list:
                if int(coord[0]) == x and int(coord[1]) == y:
                    self._data[x][y] = "X"
                    return self._data[x][y]

            self._data[x][y] = "0"
            return self._data[x][y]

        except Exception as ex:
            raise ex

    def show_planes(self):
        for x in self._computer_plane_list:
            self._data[x[0]][x[1]] = "X"

    def __str__(self):
        t = Texttable()

        # Horizontal header
        header_row = ['/']
        for i in range(self._cols):
            header_row.append(i+1)
        t.header(header_row)

        for i in range(self._rows):
            row = self._data[i]
            # Initialize vertical header
            display_row = [chr(65 + i)]

            for j in range(self._cols):
                val = self._data[i][j]
                if val == 0:
                    display_row.append(' ')
                else:
                    display_row.append(val)

            t.add_row(display_row)
        return t.draw()

    def cabin_list(self):
        # return the list of cabins as we use it for tests
        return self._computer_cabin_list

    def plane_list(self):
        # return the list of planes as we use it for tests
        return self._computer_plane_list

    def data(self):
        # return the list of data as we use it for tests
        return self._data


class PlayerBoard:
    def __init__(self, width, height):
        self._cols = width
        self._rows = height
        self._data = [[0] * self._cols for i in range(self._rows)]
        self._player_cabin_list = []
        self._player_plane_list = []
        self._validation = ValidationError()

    def set_plane(self, col, row, orientation):
        """
        In the plane list we will have all the squares occupied by the three planes of the player
        :param col: col of the cabin
        :param row: row of the cabin
        :param orientation: orientation of the cabin
        :return: None
        """
        try:
            self._validation.validate_plane(int(col), int(row), orientation, self._player_plane_list)
            self._player_cabin_list.append([row, col])
        except Exception as ex:
            raise ex

    def show_planes(self):
        for x in self._player_plane_list:
            self._data[x[0]][x[1]] = "X"

    def move(self, x, y):
        """
        :param x: the row that the COMPUTER has selected
        :param y:  the column that the COMPUTER has selected
        :return: The symbol to know the effect of this coord on the computer's table
        """
        try:
            self._validation.valid_move(x, y)
            x = int(x)
            y = int(y)
            for cab in self._player_cabin_list:
                if int(cab[0]) == x and int(cab[1]) == y:
                    self._data[x][y] = "C"
                    return self._data[x][y]

            for coord in self._player_plane_list:
                if int(coord[0]) == x and int(coord[1]) == y:
                    self._data[x][y] = "X"
                    return self._data[x][y]

            self._data[x][y] = "0"
            return self._data[x][y]

        except Exception as ex:
            raise ex

    def __str__(self):
        t = Texttable()

        # Horizontal header
        header_row = ['/']
        for i in range(self._cols):
            header_row.append(i+1)
        t.header(header_row)

        for i in range(self._rows):
            row = self._data[i]
            # Initialize vertical header
            display_row = [chr(65 + i)]

            for j in range(self._cols):
                val = self._data[i][j]
                if val == 0:
                    display_row.append(' ')
                else:
                    display_row.append(val)

            t.add_row(display_row)
        return t.draw()

    def cabin_list(self):
        # return the list of cabins as we use it for tests
        return self._player_cabin_list

    def plane_list(self):
        # return the list of planes as we use it for tests
        return self._player_plane_list

    def data(self):
        # return the list of data as we use it for tests
        return self._data


class TestPlayerBoard(unittest.TestCase):
    def setUp(self):
        self._player = PlayerBoard(10, 10)

    def test_set_plane(self):
        self._player.set_plane('2', '1', 'N')
        cabin_list = self._player.cabin_list()
        self.assertEqual(cabin_list[0][0], '1')
        self.assertEqual(cabin_list[0][1], '2')
        plane_list = self._player.plane_list()
        self.assertEqual(len(plane_list), 10)

    def test_move(self):
        self._player.set_plane('2', '1', 'N')
        symbol = self._player.move(1, 2)
        self.assertEqual(symbol, "C")
        symbol = self._player.move(9, 9)
        self.assertEqual(symbol, "0")
        symbol = self._player.move(1, 3)
        self.assertEqual(symbol, "X")

    def test_table(self):
        t = self._player.__str__()
        self.assertEqual(t[1], '-')
        self.assertEqual(len(t), 1080)

    def tearDown(self) -> None:
        self._computer = None


class TestComputerBoard(unittest.TestCase):
    def setUp(self):
        self._computer = ComputerBoard(10, 10)

    def test_set_plane(self):
        self._computer.generate_planes()
        self.assertEqual(len(self._computer.plane_list()), 30)
        self.assertEqual(len(self._computer.cabin_list()), 3)

    def test_move(self):
        self._computer.generate_planes()
        list_ = self._computer.cabin_list()
        x = list_[0][0]
        y = list_[0][1]
        self.assertEqual(self._computer.move(x, y), "C")
        self.assertEqual(self._computer.move(2, 0), '0')
        symbol = self._computer.move(1, 3)
        self.assertEqual(symbol, "X")

    def test_table(self):
        t = self._computer.__str__()
        self.assertEqual(t[1], '-')
        self.assertEqual(len(t), 1080)

    def tearDown(self) -> None:
        self._computer = None
