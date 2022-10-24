import unittest
import random

from board import PlayerBoard, ComputerBoard


class ComputerMove:
    def __init__(self, player, computer):
        self._player = player
        self._computer = computer

    def generate_move(self):
        """
        :return: the chosen coordinates for the computer's turn
        """
        coords = []
        x = random.randint(0, 9)
        y = random.randint(0, 9)
        player_cabins = self._player.cabin_list()
        for cab in player_cabins:
            if int(cab[0]) == x and int(cab[1]) == y:
                return x, y

        is_plane = False
        player_plane_list = self._player.plane_list()
        for coord in player_plane_list:
            if int(coord[0]) == x and int(coord[1]) == y:
                is_plane = True

        if is_plane:
            for i in range(x - 3, x + 4):
                for j in range(y - 3, y + 4):
                    if i >= 0 and j >= 0:
                        coords.append((i, j))
            x = random.choice(coords[0])
            y = random.choice(coords[1])
        return x, y

    def move(self, x, y):
        """
        :param x: the row that the COMPUTER has selected
        :param y: the column that the COMPUTER has selected
        :return: The symbol to count the cabins
        """
        try:
            symbol = self._player.move(x, y)
            return symbol
        except Exception as ex:
            raise ex


class PlayerMove:
    def __init__(self, player, computer):
        self._player = player
        self._computer = computer

    def move(self, x, y):
        """
        :param x: the row that the player has selected
        :param y: the column that the player has selected
        :return: The symbol to count the cabins
        """
        try:
            symbol = self._computer.move(x, y)
            return symbol
        except Exception as ex:
            raise ex


class TestPlayerMove(unittest.TestCase):
    def setUp(self):
        self._player = PlayerBoard(10, 10)
        self._computer = ComputerBoard(10, 10)
        self._player.set_plane(2, 1, 'N')
        self._player_move = PlayerMove(self._player, self._computer)

    def test_move(self):
        symbol = self._player_move.move(1, 2)
        self.assertEqual(symbol, "0")
        symbol = self._player_move.move(6, 7)
        self.assertEqual(symbol, "0")
        symbol = self._player_move.move(1, 3)
        self.assertEqual(symbol, "0")


class TestComputerMove(unittest.TestCase):
    def setUp(self):
        self._player = PlayerBoard(10, 10)
        self._computer = ComputerBoard(10, 10)
        self._player.set_plane(2, 1, 'N')
        self._computer_move = ComputerMove(self._player, self._computer)

    def test_move(self):
        symbol = self._computer_move.move(1, 2)
        self.assertEqual(symbol, "C")
        symbol = self._computer_move.move(6, 7)
        self.assertEqual(symbol, "0")
        symbol = self._computer_move.move(1, 3)
        self.assertEqual(symbol, "X")
