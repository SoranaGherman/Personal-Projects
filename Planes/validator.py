import unittest
from exception import ValidationErrors


class ValidationError(Exception):
    def __init__(self):
        self.plane_coord = []

    def validate_plane(self, col, row, orientation, plane_list):
        """
        :param col: the selected column
        :param row: the selected row
        :param orientation: The orientation of the plane
        :param plane_list: all the squares which are not empty
        :return: None
        """
        # we verify if the plane is inside the table
        self.plane_coord = list()
        if int(row) > 9 or int(row) < 0 or int(col) > 9 or int(col) < 0:
            raise Exception("Invalid input!")

        if orientation.lower() == "n":
            if (col - 2) < 0 or (col + 2) > 9 or (row - 1) < 0 or (row + 2) > 9:
                raise Exception("Plane outside the table!")

            self.plane_coord.append([row, col - 2])
            self.plane_coord.append([row, col - 1])
            self.plane_coord.append([row, col])
            self.plane_coord.append([row, col + 1])
            self.plane_coord.append([row, col + 2])
            self.plane_coord.append([row + 1, col])
            self.plane_coord.append([row - 1, col])
            self.plane_coord.append([row + 2, col])
            self.plane_coord.append([row + 2, col - 1])
            self.plane_coord.append([row + 2, col + 1])

        elif orientation.lower() == "s":
            if (col - 2) < 0 or (col + 2) > 9 or (row + 1) > 9 or (row - 2) < 0:
                raise Exception("Plane outside the table!")

            self.plane_coord.append([row, col - 2])
            self.plane_coord.append([row, col - 1])
            self.plane_coord.append([row, col])
            self.plane_coord.append([row, col + 1])
            self.plane_coord.append([row, col + 2])
            self.plane_coord.append([row + 1, col])
            self.plane_coord.append([row - 1, col])
            self.plane_coord.append([row - 2, col])
            self.plane_coord.append([row - 2, col - 1])
            self.plane_coord.append([row - 2, col + 1])

        elif orientation.lower() == "e":
            if (row + 2) > 9 or (row - 2) < 0 or (col + 1) > 9 or (col - 2) < 0:
                raise Exception("Plane outside the table!")

            self.plane_coord.append([row - 1, col])
            self.plane_coord.append([row - 2, col])
            self.plane_coord.append([row + 1, col])
            self.plane_coord.append([row + 2, col])
            self.plane_coord.append([row, col])
            self.plane_coord.append([row, col - 2])
            self.plane_coord.append([row, col - 1])
            self.plane_coord.append([row, col + 1])
            self.plane_coord.append([row - 1, col - 2])
            self.plane_coord.append([row + 1, col - 2])

        elif orientation.lower() == "v":
            if (row + 2) > 9 or (row - 2) < 0 or (col + 2) > 9 or (col - 1) < 0:
                raise Exception("Plane outside the table!")

            self.plane_coord.append([row - 1, col])
            self.plane_coord.append([row - 2, col])
            self.plane_coord.append([row + 1, col])
            self.plane_coord.append([row + 2, col])
            self.plane_coord.append([row, col])
            self.plane_coord.append([row, col + 2])
            self.plane_coord.append([row - 1, col + 2])
            self.plane_coord.append([row + 1, col + 2])
            self.plane_coord.append([row, col - 1])
            self.plane_coord.append([row, col + 1])

        else:
            raise Exception("The orientation must be N, S, E or V")

        # if we reach this, it means that the plane is not outside the table
        # now we verify if the plane do not intersect others

        for coord in self.plane_coord:
            for exist_coord in plane_list:
                if coord[0] == exist_coord[0] and coord[1] == exist_coord[1]:
                    raise Exception("Planes must not overlap!")

        # the plane is ok, hence we append the coordinates to the plane list
        for coord in self.plane_coord:
            plane_list.append(coord)

    @staticmethod
    def valid_move(x, y):
        """"
        :param x: The row
        :param y: The col
        :return: None
        """
        if int(x) > 9 or int(x) < 0 or int(y) > 9 or int(y) < 0:
            raise Exception("Invalid move!")

        return True


class ValidationTest(unittest.TestCase):
    def setUp(self):
        self.list_ = ValidationError()

    def test_validation_plane(self):
        self.list_.validate_plane(2, 1, 'N', [])
        list_ = self.list_.plane_coord
        self.assertEqual(len(list_), 10)
        self.list_.validate_plane(8, 4, 'E', [])
        list_ = self.list_.plane_coord
        self.assertEqual(len(list_), 10)
        self.list_.validate_plane(4, 6, 'S', [])
        list_ = self.list_.plane_coord
        self.assertEqual(len(list_), 10)
        self.list_.validate_plane(4, 6, 'V', [])
        list_ = self.list_.plane_coord
        self.assertEqual(len(list_), 10)

        plane_list = list()
        self.list_.validate_plane(2, 1, 'N', plane_list)
        self.assertEqual(len(plane_list), 10)

    def test_valid_move(self):
        self.assertEqual(self.list_.valid_move(1, 2), True)
