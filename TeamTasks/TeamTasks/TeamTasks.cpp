// TeamTasks.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cstdint>
#include <tuple>
#include <map>
#include <vector>
using namespace std;

enum class TaskStatus {
    NEW,          // новая
    IN_PROGRESS,  // в разработке
    TESTING,      // на тестировании
    DONE          // завершена
};

using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
private:
    map<string, TasksInfo> workers;
public:
    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo& GetPersonTasksInfo(const string& person) const {
        auto& res = workers.at(person);
        return res;
    }

    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const string& person) {
        workers[person][TaskStatus::NEW] += 1;
    }

    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(
        const string& person, int task_count) {
        TasksInfo first;
        TasksInfo second = workers[person];
        updater(first, second, TaskStatus::NEW, TaskStatus::IN_PROGRESS, person, task_count);
        updater(first, second, TaskStatus::IN_PROGRESS, TaskStatus::TESTING, person, task_count);
        updater(first, second, TaskStatus::TESTING, TaskStatus::DONE, person, task_count);
        return make_tuple(first, second);
    }
    void updater(TasksInfo& first, TasksInfo& second, TaskStatus toClean, TaskStatus toUpd, const string& person, int& task_count) {
        while (workers[person][toClean] > 0 && task_count > 0) {
            task_count--;
            workers[person][toClean]--;
            workers[person][toUpd]++;
            first[toUpd]++;
            second[toClean]--;
        }
        if (second[toClean] == 0)
            second.erase(toClean);
    }
};

/*void updater(map<string, TasksInfo>& workers, TasksInfo& first, TasksInfo& second, TaskStatus toClean, TaskStatus toUpd, const string& person, int& task_count) {
    while (workers[person][toClean] > 0 && task_count > 0) {
        task_count--;
        workers[person][toClean]--;
        workers[person][toUpd]++;
        first[toUpd]++;
        second[toClean]--;
    }
    if (second[toClean] == 0)
        second.erase(toClean);
}*/
// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
    cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
        ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
        ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
        ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}
int main() {
    TeamTasks tasks;
    tasks.AddNewTask("Ilia");
    for (int i = 0; i < 3; ++i) {
        tasks.AddNewTask("Ivan");
    }
    cout << "Ilia's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
    cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

    TasksInfo updated_tasks, untouched_tasks;

    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
        PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    return 0;
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
