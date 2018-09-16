import time
import itertools
import tkinter as tk

from solver import Solver
from status import Status

# WINDOW PARAMETER

MARGIN = 20
SIDE   = 50
WIDTH  = HEIGHT = MARGIN * 2 + SIDE * 9

class Ui(tk.Frame):
    """
    Graphical user interface for accepting sudoku input
    """
    def __init__(self, master, game):
        self.master = master
        tk.Frame.__init__(self, master)
        
        self.game = game
        self.row, self.col = -1, -1

        self.__initUI()

    def __initUI(self):
        self.pack(fill="both", expand=1)

        self.canvas = tk.Canvas(self, width=WIDTH, height=HEIGHT)
        self.canvas.pack(fill="both", side="top")

        self.message = tk.StringVar()
        self.message.set("I solve Sudoku puzzles")
        self.messageLabel = tk.Label(self, textvariable=self.message, justify="center")
        self.messageLabel.pack()

        solveButton = tk.Button(self, text="Solve", command=self.__solve)
        solveButton.pack(fill="x", padx="10", pady="5")

        clearButton = tk.Button(self, text="Clear", command=self.__clear)
        clearButton.pack(fill="x", padx="10", pady="5")

        self.__draw_grid()

        self.canvas.bind("<Button-1>", self.__cell_clicked)
        self.canvas.bind("<Key>", self.__key_pressed)

    def __draw_grid(self):
        for i in range(10):
            color = "blue" if i % 3 == 0 else "gray"
            width = 2 if i % 3 == 0 else 1

            x0 = MARGIN + i * SIDE
            y0 = MARGIN
            x1 = MARGIN + i * SIDE
            y1 = HEIGHT - MARGIN
            self.canvas.create_line(x0, y0, x1, y1, fill=color, width=width)

            x0 = MARGIN
            y0 = MARGIN + i * SIDE
            x1 = WIDTH - MARGIN
            y1 = MARGIN + i * SIDE
            self.canvas.create_line(x0, y0, x1, y1, fill=color, width=width)

    def __draw_cursor(self):
        self.canvas.delete("cursor")
        if self.row >= 0 and self.col >= 0:
            x0 = MARGIN + self.col * SIDE + 1
            y0 = MARGIN + self.row * SIDE + 1
            x1 = MARGIN + (self.col + 1) * SIDE + 1
            y1 = MARGIN + (self.row + 1) * SIDE + 1
            self.canvas.create_rectangle(x0, y0, x1, y1, outline="red", tags="cursor")

    def __cell_clicked(self, event):
        x, y = event.x, event.y
        if MARGIN < x < WIDTH - MARGIN and MARGIN < y < HEIGHT - MARGIN:
            self.canvas.focus_set()

            row, col = (y - MARGIN) // SIDE, (x - MARGIN) // SIDE

            if (row, col) == (self.row, self.col):
                self.row, self.col = -1, -1

            self.row, self.col = row, col

        self.__draw_cursor()

    def __key_pressed(self, event):
        if self.row >= 0 and self.col >= 0 and event.char in "123456789":
            self.game.puzzle[self.row][self.col] = [int(event.char)]
            self.__draw_puzzle()
            self.__draw_cursor()
            self.col, self.row = -1, -1

    def __clear(self):
        self.game.start()
        self.__draw_puzzle()

    def __solve(self):
        start = time.time()
        status = self.game.solve()
        end = time.time()
        duration = end - start
        if status == Status.UNIQUE:
            self.__draw_puzzle()
            self.message.set("This puzzle is solved in %d miliseconds!" % (duration * 1000))
        elif status == Status.IMPOSSIBLE:
            self.message.set("This puzzle cannot be solved.")
        elif status == Status.MISSING:
            self.__draw_puzzle()
            self.message.set("This puzzle has multiple solutions.")

    def __draw_puzzle(self):
        self.canvas.delete("numbers")
        for i, j in itertools.product(range(9), repeat=2):
            number = self.game.puzzle[i][j]
            if len(number) == 1:
                x = MARGIN + j * SIDE + SIDE // 2
                y = MARGIN + i * SIDE + SIDE // 2
                self.canvas.create_text(x, y, text=number, tags="numbers", fill="black")

if __name__ == '__main__':

    window = tk.Tk()
    window.title("Sudoku Solver")
    window.resizable(width=False, height=False)

    solver = Solver()

    ui = Ui(window, solver)

    window.mainloop()