import tkinter as tk
import itertools

from status import Status

class Solver:

    def __init__(self):
        self.start()

    def start(self):
        self.puzzle = []
        for i in range(9):
            self.puzzle.append([])
            for j in range(9):
                self.puzzle[i].append([1, 2, 3, 4, 5, 6, 7, 8, 9])

    def status(self):
        print(self.puzzle)
        for i in range(9):
            for j in range(9):
                if len(self.puzzle[i][j]) == 0:
                    return Status.IMPOSSIBLE
        for i in range(9):
            if len(set([x for j in range(9) for x in self.puzzle[i][j]])) < 9:
                return Status.IMPOSSIBLE
            if len(set([x for j in range(9) for x in self.puzzle[j][i]])) < 9:
                return Status.IMPOSSIBLE
        for i, j in itertools.product(range(3), repeat=2):
            square = set()
            for kp in range(i * 3, i * 3 + 3):
                for kq in range(j * 3, j * 3 + 3):
                    for num in self.puzzle[kp][kq]:
                        square.add(num)
            if len(square) < 9:
                return Status.IMPOSSIBLE

        for i in range(9):
            for j in range(9):
                if len(self.puzzle[i][j]) > 1:
                    return Status.MISSING
        return Status.UNIQUE


    def solve(self):
        progress = True
        while progress:
            progress = False
            progress = progress or self.redundantChoiceRemoval()
            progress = progress or self.onlyChoiceRule()
            progress = progress or self.subgroupElimination()
            progress = progress or self.hiddenTwinExclusion()
            progress = progress or self.nakedTwinExclusion()
        return self.status()

    def redundantChoiceRemoval(self):
        worked = False
        for i, j in itertools.product(range(9), repeat=2):
            if len(self.puzzle[i][j]) == 1:
                c = self.puzzle[i][j][0]
                # row
                for k in range(9):
                    if k == j:
                        continue
                    if c in self.puzzle[i][k]:
                        self.puzzle[i][k].remove(c)
                        if len(self.puzzle[i][k]) == 1:
                            self.puzzle[i][k] = [self.puzzle[i][k][0]]
                            worked = True
                # col
                for k in range(9):
                    if k == i:
                        continue
                    if c in self.puzzle[k][j]:
                        self.puzzle[k][j].remove(c)
                        if len(self.puzzle[k][j]) == 1:
                            self.puzzle[k][j] = [self.puzzle[k][j][0]]
                            worked = True

                # box
                p = (i // 3) * 3
                q = (j // 3) * 3
                for kp in range(p, p + 3):
                    for kq in range(q, q + 3):
                        if kp == i and kq == j:
                            continue
                        if c in self.puzzle[kp][kq]:
                            self.puzzle[kp][kq].remove(c)
                            if len(self.puzzle[kp][kq]) == 1:
                                self.puzzle[kp][kq] = [self.puzzle[kp][kq][0]]
                                worked = True
        return worked

    def onlyChoiceRule(self):
        worked = False
        for i, j in itertools.product(range(9), repeat=2):
            if len(self.puzzle[i][j]) == 1:
                continue
            for c in self.puzzle[i][j]:
                isOnlyChoice = True
                # row
                for k in range(9):
                    if k == j:
                        continue
                    if c in self.puzzle[i][k]:
                        isOnlyChoice = False
                        break
                if isOnlyChoice:
                    self.puzzle[i][j] = [c]
                    worked = True
                    break
                
                isOnlyChoice = True
                for k in range(9):
                    if k == i:
                        continue
                    if c in self.puzzle[k][j]:
                        isOnlyChoice = False
                        break
                if isOnlyChoice:
                    self.puzzle[i][j] = [c]
                    worked = True
                    break

                isOnlyChoice = True
                p = (i // 3) * 3
                q = (j // 3) * 3
                for kp in range(p, p + 3):
                    for kq in range(q, q + 3):
                        if kp == i and kq == j:
                            continue
                        if c in self.puzzle[kp][kq]:
                            isOnlyChoice = False
                            break
                if isOnlyChoice:
                    self.puzzle[i][j] = [c]
                    worked = True
                    break
        return worked

    def subgroupElimination(self):
        worked = False
        for c in range(1, 10):
            for gi in range(3):
                for gj in range(3):
                    row = [0, 0, 0]
                    col = [0, 0, 0]
                    for i in range(gi * 3, gi * 3 + 3):
                        for j in range(gj * 3, gj * 3 + 3):
                            if c in self.puzzle[i][j]:
                                row[i % 3] = 1
                                col[j % 3] = 1
                    if sum(row) == 1:
                        k = 0
                        for x in range(3):
                            if row[x] == 1:
                                k = x
                        for j in range(9):
                            if j in range(gj * 3, gj * 3 + 3):
                                continue
                            if c in self.puzzle[gi * 3 + k][j]:
                                self.puzzle[gi * 3 + k][j].remove(c)
                                if len(self.puzzle[gi * 3 + k][j]) == 1:
                                    self.puzzle[gi * 3 + k][j] = [self.puzzle[gi * 3 + k][j][0]]
                                worked = True
                    if sum(col) == 1:
                        k = 0
                        for x in range(3):
                            if col[x] == 1:
                                k = x
                        for i in range(9):
                            if i in range(gi * 3, gi * 3 + 3):
                                continue
                            if c in self.puzzle[i][gj * 3 + k]:
                                self.puzzle[i][gj * 3 + k].remove(c)
                                if len(self.puzzle[i][gj * 3 + k]) == 1:
                                    self.puzzle[i][gj * 3 + k] = [self.puzzle[i][gj * 3 + k][0]]
                                worked = True
        return worked

    def hiddenTwinExclusion(self):
        worked = False
        for c1 in range(1, 10):
            for c2 in range(c1 + 1, 10):
                # row
                for i in range(9):
                    cnt = 0
                    for j in range(9):
                        if c1 in self.puzzle[i][j] and c2 in self.puzzle[i][j]:
                            cnt += 1
                        elif c1 in self.puzzle[i][j] or c2 in self.puzzle[i][j]:
                            cnt = -1
                            break
                    
                    if cnt != 2:
                        continue

                    for j in range(9):
                        if c1 in self.puzzle[i][j] and c2 in self.puzzle[i][j]:
                            if len(self.puzzle[i][j]) > 2:
                                worked = True
                                self.puzzle[i][j] = [c1, c2]

                # col
                for j in range(9):
                    cnt = 0
                    for i in range(9):
                        if c1 in self.puzzle[i][j] and c2 in self.puzzle[i][j]:
                            cnt += 1
                        elif c1 in self.puzzle[i][j] or c2 in self.puzzle[i][j]:
                            cnt = -1
                            break

                    if cnt != 2:
                        continue

                    for i in range(9):
                        if c1 in self.puzzle[i][j] and c2 in self.puzzle[i][j]:
                            if len(self.puzzle[i][j]) > 2:
                                worked = True
                                self.puzzle[i][j] = [c1, c2]

                #box
                for gi in range(3):
                    for gj in range(3):
                        cnt = 0
                        for i in range(gi * 3, gi * 3 + 3):
                            if cnt == -1:
                                break
                            for j in range(gj * 3, gj * 3 + 3):
                                if c1 in self.puzzle[i][j] and c2 in self.puzzle[i][j]:
                                    cnt += 1
                                elif c1 in self.puzzle[i][j] or c2 in self.puzzle[i][j]:
                                    cnt = -1
                                    break

                        if cnt != 2:
                            continue
                        # print(c1, c2, gi, gj)
                        return False
                        for i in range(gi * 3, gi * 3 + 3):
                            for j in range(gj * 3, gj * 3 + 3):
                                if c1 in self.puzzle[i][j] and c2 in self.puzzle[i][j]:
                                    if len(self.puzzle[i][j]) > 2:
                                        worked = True
                                        self.puzzle[i][j] = [c1, c2]
        return worked


    def nakedTwinExclusion(self):
        worked = False
        for i, j in itertools.product(range(9), repeat=2):
            if len(self.puzzle[i][j]) != 2:
                continue
            
            c1 = self.puzzle[i][j][0]
            c2 = self.puzzle[i][j][1]

            # row
            for k in range(9):
                if k == j:
                    continue
                if self.puzzle[i][k] == self.puzzle[i][j]:
                    for x in range(9):
                        if x == j or x == k:
                            continue
                        if c1 in self.puzzle[i][x]:
                            worked = True
                            self.puzzle[i][x].remove(c1)
                            if len(self.puzzle[i][x]) == 1:
                                self.puzzle[i][x] = [self.puzzle[i][x][0]]
                        if c2 in self.puzzle[i][x]:
                            worked = True
                            self.puzzle[i][x].remove(c2)
                            if len(self.puzzle[i][x]) == 1:
                                self.puzzle[i][x] = [self.puzzle[i][x][0]]
                        
            # col
            for k in range(9):
                if k == i:
                    continue
                if self.puzzle[k][j] == self.puzzle[i][j]:
                    for x in range(9):
                        if x == i or x == k:
                            continue
                        if c1 in self.puzzle[x][j]:
                            worked = True
                            self.puzzle[x][j].remove(c1)
                            if len(self.puzzle[x][j]) == 1:
                                self.puzzle[x][j] = [self.puzzle[x][j][0]]
                        if c2 in self.puzzle[x][j]:
                            worked = True
                            self.puzzle[x][j].remove(c2)
                            if len(self.puzzle[x][j]) == 1:
                                self.puzzle[x][j] = [self.puzzle[x][j][0]]
                            
        return worked
