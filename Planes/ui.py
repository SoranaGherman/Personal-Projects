import random

from board import PlayerBoard, ComputerBoard
from move import PlayerMove, ComputerMove


class Ui:
    def __init__(self):
        self._player = PlayerBoard(10, 10)
        self._computer = ComputerBoard(10, 10)
        self._player_move = PlayerMove(self._player, self._computer)
        self._computer_move = ComputerMove(self._player, self._computer)

    def start(self):
        print("Welcome to Planes!")
        index = 0
        # the planes of the player
        while index < 3:
            try:
                cabin = input("Enter the coordinates of the cabin: ")
                orientation = input("Enter the orientation of the plane: ")
                row = ord(cabin[0]) - 65
                col = int(cabin[1:]) - 1
                self._player.set_plane(col, row, orientation)
                index += 1

            except Exception as ve:
                print(str(ve))

        self._computer.generate_planes()

        count_player, count_computer = 0, 0
        player_turn = True
        while count_player != 3 and count_computer != 3:
            try:
                print("COMPUTER BOARD")
                print(self._computer)
                print("PLAYER BOARD")
                print(self._player)
                if player_turn:
                    print("It is your turn!")
                    player_turn = False
                    cabin = input("Enter a move: ")
                    row = ord(cabin[0]) - 65
                    col = int(cabin[1:]) - 1
                    symbol = self._player_move.move(row, col)
                    if symbol == "C":
                        print("You have crashed this plane!!")
                        count_player += 1
                else:
                    player_turn = True
                    row, col = self._computer_move.generate_move()
                    print("Computer picked the cell " + chr(row + 65) + str(col + 1))
                    symbol = self._computer_move.move(row, col)
                    if symbol == "C":
                        print("The COMPUTER has crashed this plane!!")
                        count_computer += 1

            except Exception as ve:
                print(str(ve))

        if not player_turn:
            print("You won!")

        else:
            print("Computer won!")


console = Ui()
console.start()
