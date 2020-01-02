"""
Created on 24 nov. 2016

@author: bogdanleanca
"""


class UndoController:
    def __init__(self):
        self._operations = []
        self._index = -1
        self._recorded = True

    def record_operation(self, operation):
        if self.is_recorded():
            self._operations[-1].append(operation)
            return True

        return False

    def new_operation(self):
        if not self.is_recorded():
            return

        self._operations = self._operations[0:self._index + 1]
        self._operations.append([])
        self._index += 1

    def is_recorded(self):
        return self._recorded

    def undo(self):
        if self._index < 0:
            return False

        self._recorded = False

        for operation in self._operations[self._index]:
            operation.undo()

        self._recorded = True

        self._index -= 1
        return True

    def redo(self):
        if self._index >= len(self._operations) - 1:
            return False

        self._recorded = False

        for operation in self._operations[self._index + 1]:
            operation.redo()

        self._recorded = True

        self._index += 1
        return True


class FunctionCall:
    def __init__(self, function_reference, *parameters):
        self._function_reference = function_reference
        self._parameters = parameters

    def call(self):
        self._function_reference(*self._parameters)

    def __str__(self):
        return str(self._function_reference) + " + " + str(self._parameters)


class Operation:
    def __init__(self, function_do, function_undo):
        self._function_do = function_do
        self._function_undo = function_undo

    def undo(self):
        self._function_undo.call()

    def redo(self):
        self._function_do.call()

    def __str__(self):
        return str(self._function_undo) + " + " + str(self._function_do)
