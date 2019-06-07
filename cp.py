from ortools.linear_solver import pywraplp
from ortools.sat.python import cp_model
from pathlib import Path


class RPQ:
    def __init__(self, r, p, q):
        self.R = r
        self.P = p
        self.Q = q



def cp(jobs, instance_name):
    model = cp_model.CpModel()

    variables_max_value = 0
    for i in range(len(jobs)):
        variables_max_value += (jobs[i].R + jobs[i].P + jobs[i].Q)

    # variables :
    alfa_matrix = {}
    for i in range(len(jobs)):
        for j in range(len(jobs)):
            alfa_matrix[i, j] = model.NewIntVar(0, 1, "alfa" + str(i) + "_" + str(j))
    starts = []
    for i in range(len(jobs)):
        starts.append(model.NewIntVar(0, variables_max_value, "starts" + str(i)))
    cmax = model.NewIntVar(0, variables_max_value, "cmax")

    for i in range(len(jobs)):
        model.Add(starts[i] >= jobs[i].R)
        model.Add(cmax >= starts[i] + jobs[i].P + jobs[i].Q)

    for i in range(len(jobs)):
        for j in range(i + 1, len(jobs)):
            model.Add(starts[i] + jobs[i].P <= starts[j] + alfa_matrix[i, j] * variables_max_value)
            model.Add(starts[j] + jobs[j].P <= starts[i] + alfa_matrix[j, i] * variables_max_value)
            model.Add(alfa_matrix[i, j] + alfa_matrix[j, i] == 1)

    # solver:
    model.Minimize(cmax)

    solver = cp_model.CpSolver()
    solver.parameters.max_time_in_seconds = 120.0
    solver.Solve(model)
    print(instance_name, "Cmax:", solver.ObjectiveValue())
    pi = []
    for i in range(len(starts)):
        pi.append((i, solver.Value(starts[i])))
    pi.sort(key=lambda x: x[1])
    show = [x[0] for x in pi]
    print(show)


def GetRPQsFromFile(pathToFile):
    fullTextFromFile = Path(pathToFile).read_text()
    words=fullTextFromFile.replace("\n"," ").split(" ")
    words_cleaned=list(filter(None,words))
    numbers=list(map(int,words_cleaned))
    numberOfJobs=numbers[0]
    numbers.pop(0)
    numbers.pop(0)
    jobs=[]
    for i in range(numberOfJobs):
        jobs.append(RPQ(numbers[0],numbers[1],numbers[2]))
        numbers.pop(0)
        numbers.pop(0)
        numbers.pop(0)
    return jobs


if __name__ == '__main__':
    file_paths=["in100.txt"]
    for i in range(len(file_paths)):
        jobs=GetRPQsFromFile(file_paths[i])
        cp(jobs,file_paths[i])
