#include "z:\std_lib_facilities.h"
#include "Chrono.h"
using namespace Chrono;

void f()
{
	Date t;
	Date today{ 2013,Month::mar,7 };
	today.count_day();
	cout << today << " From (1970-1-1) total days: " << today.all_days() << endl;
	
	Date in_date;
	Date tomorrow{ today };
	cout << "Please enter date(e.g., (2000-2-29)): ";
	while (cin >> in_date)
	{
		tomorrow = in_date;
		cout << "input date is: " << tomorrow << endl;
				
		Date t{ tomorrow };	
		for (int i = 0;i < 8;++i) {
			t = next_workday(t);
			t.count_day();
			cout << "The next workday is:" << t << " day of week is: " << int(day_of_week(t)) << endl;
			cout << "The day is week of year: " << week_of_year(t) << " weeks." << endl;
			cout << t << " From (1970-1-1) total days: " << t.all_days() << endl;
		}
		cout << "Day of week: " << int(day_of_week(tomorrow)) << endl;
		
		cout << "The next Sunday: " << next_Sunday(tomorrow) << endl;

		cout << "The next weekday: " << next_weekday(tomorrow) << endl;
		
		int i;
		cout << "Please enter number for add_day: ";
		cin >> i ;
		tomorrow.add_day(i);
		cout << "Add " << i << " day" << ((i > 1) ? "s" : "") << ", the date is: " << tomorrow << endl;

		cout << "Please enter number for add_month: ";
		cin >> i ;
		tomorrow.add_month(i);
		cout << "Add " << i << " month" << ((i>1)?"s":"") << ", the date is : " << tomorrow << endl;

		cout << "Please enter number for add_year: ";
		cin >> i ;
		tomorrow.add_year(i);
		cout << "Add " << i << " year" << ((i > 1) ? "s" : "") << ", the date is" << tomorrow << endl;
		
		cout << "Please enter date(e.g., (2000-2-29)): ";
	}
}

int main(int argc, char* argv[], char* env[])
{
	//arguments and envrionments
	vector <string> in_argv, in_env;
	for (int i = 0; i < argc; ++i)
		in_argv.push_back(argv[i]);
	for (int i = 0; env[i] != NULL; ++i)
		in_env.push_back(env[i]);
	//display arguments and envrionments
	cout << "Argument" << (in_argv.size() > 1 ? "s: " : ": ") << endl;
	for (auto v : in_argv)
		cout << v << endl;

	cout << "Environment" << ((in_env.size() > 1) ? "s: " : ": ") << endl;
	for (auto v : in_env)
		cout << v << endl;
/**/
	//Chrono
	try {
		f();
	}
	catch (runtime_error& e) {
		cout << e.what() << endl;
	}
	catch (exception& e) {
		cerr << "\nexception:" << e.what() << endl;
		return 1;
	}
	catch (...) {
		cerr << "other exception\n";
		return 2;
	}
}