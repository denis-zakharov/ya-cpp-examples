#include <map>
#include <string>
#include <tuple>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

enum class TaskStatus {
	NEW,          // новая
	IN_PROGRESS,  // в разработке
	TESTING,      // на тестировании
	DONE          // завершена
};

ostream& operator <<(ostream& out, const TaskStatus& status) {
	string statusName;
	switch (status) {
	case TaskStatus::NEW:
		statusName = "\"NEW\"";
		break;
	case TaskStatus::IN_PROGRESS:
		statusName = "\"IN_PROGRESS\"";
		break;
	case TaskStatus::TESTING:
		statusName = "\"TESTING\"";
		break;
	case TaskStatus::DONE:
		statusName = "\"DONE\"";
		break;
	}
	return out << statusName;
}

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:
	// Получить статистику по статусам задач конкретного разработчика
	const TasksInfo& GetPersonTasksInfo(const string& person) const {
		return team_tasks.at(person);
	}

	// Добавить новую задачу (в статусе NEW) для конкретного разработчитка
	void AddNewTask(const string& person) {
		TasksInfo& person_tasks = team_tasks[person];
		person_tasks[TaskStatus::NEW]++;
	}

	// Обновить статусы по данному количеству задач конкретного разработчика
	tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count) {
		if (team_tasks.count(person) == 0) {
			return make_tuple(TasksInfo(), TasksInfo());
		}
		TasksInfo& person_tasks = team_tasks.at(person);
		int tasks_new = person_tasks[TaskStatus::NEW];
		int tasks_in = person_tasks[TaskStatus::IN_PROGRESS];
		int tasks_t = person_tasks[TaskStatus::TESTING];
		
		TasksInfo updated;
		while (task_count > 0) {
			task_count--;
			if (tasks_new > 0) {
				tasks_new--;
				person_tasks[TaskStatus::NEW]--;
				updated[TaskStatus::IN_PROGRESS]++;
			}
			else if (tasks_in > 0) {
				tasks_in--;
				person_tasks[TaskStatus::IN_PROGRESS]--;
				updated[TaskStatus::TESTING]++;
			}
			else if (tasks_t > 0) {
				tasks_t--;
				person_tasks[TaskStatus::TESTING]--;
				updated[TaskStatus::DONE]++;
			}
			else {
				// no more tasks
				break;
			}
		}

		// updated, untouched (except completed)
		TasksInfo untouched = ComputeUntouched(person_tasks, updated);
		return make_tuple(updated, untouched);
	}
private:
	map<string, TasksInfo> team_tasks;
	TasksInfo ComputeUntouched(TasksInfo& for_person, TasksInfo& updated) {
		TasksInfo result;
		TaskStatus status = TaskStatus::NEW;
		for (const auto& status : { TaskStatus::NEW, TaskStatus::IN_PROGRESS, TaskStatus::TESTING }) {
			int count = for_person[status];
			if (count > 0) {
				result[status] = count;
			}
		}
		// merge updated to tasks for person
		MergeUpdated(for_person, updated);
		return result;
	}
	void MergeUpdated(TasksInfo& for_person, TasksInfo& updated) {
		for (const auto&[key, value] : updated) {
			for_person[key] += value;
		}
	}
};


template <typename Collection>
string Join(const Collection& c, const string& d) {
	stringstream ss;
	bool isFirst = true;
	for (const auto& i : c) {
		if (!isFirst) {
			ss << d;
		}
		isFirst = false;
		ss << i;
	}
	return ss.str();
}

template <typename F, typename S>
ostream& operator <<(ostream& out, const pair<F, S>& p) {
	return out << p.first << ": " << p.second;
}

template <typename K, typename V>
ostream& operator <<(ostream& out, const map<K, V>& m) {
	return out << '{' << Join(m, ", ") << '}';
}

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& v) {
	return out << '[' << Join(v, ", ") << ']';
}

int main() {
	TeamTasks tasks;
	ifstream input("TestInput.txt");
	string line;
	
	while (getline(input, line)) {
		string command, person;
		int num;
		stringstream sin(line);
		sin >> command >> person;
		if (command == "AddNewTasks") {
			sin >> num;
			while (num--)
				tasks.AddNewTask(person);
			cout << "[]" << endl;
		}
		else if (command == "PerformPersonTasks") {
			sin >> num;
			TasksInfo updated_tasks, untouched_tasks;
			tie(updated_tasks, untouched_tasks) =
				tasks.PerformPersonTasks(person, num);
			cout << vector<TasksInfo>{updated_tasks, untouched_tasks } << endl;
		}
		else if (command == "GetPersonTasksInfo") {
			cout << tasks.GetPersonTasksInfo(person) << endl;
		}
		else if (command.size() && command[0] != '#') {
			throw invalid_argument("wrong command: " + command);
		}
	}

	return 0;
}