void listAll(const Class* c, string path)  // two-parameter overload
{
	path = path + c->name();
	if (c->subclasses().size() == 0) {
		cout << path << endl;
		return;
	}
	cout << path << endl;
	path = path + "==>";
	for (int i = 0; i < c->subclasses().size(); i++) {
		listAll(c->subclasses()[i], path);
	}

}