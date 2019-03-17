struct Lecture {
	string title;
	int duration;
	string author;
};

void PrintLecture(Lecture lecture) {
	cout << "Title: " << lecture.title <<
		", duration: " << lecture.duration <<
		", author: " << lecture.author << "\n";
}

