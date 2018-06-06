#include "stdafx.h"
#include "../CAdvancedStudent.cpp"
#include "../CPupil.cpp"
#include "../CStudent.cpp"
#include "../CTeacher.cpp"
#include "../CWorker.cpp"

TEST_CASE("CPupil")
{
	CPupil pupil("Alex", "Ovechkin", "OVI", "Washington, USA", "Moscow schoool", "9d");

	GIVEN("Initially")
	{
		WHEN("Initially")
		{
			THEN("allow get first name")
			{
				REQUIRE(pupil.GetFirstName() == "Alex");
			}

			THEN("allow get last name")
			{
				REQUIRE(pupil.GetLastName() == "Ovechkin");
			}

			THEN("allow get middlename name")
			{
				REQUIRE(pupil.GetMiddleName() == "OVI");
			}

			THEN("allow get address")
			{
				REQUIRE(pupil.GetAddress() == "Washington, USA");
			}

			THEN("allow get school name")
			{
				REQUIRE(pupil.GetSchoolName() == "Moscow schoool");
			}

			THEN("allow get class number")
			{
				REQUIRE(pupil.GetClassNumber() == "9d");
			}
		}

		WHEN("set new value")
		{
			THEN("allow set first name")
			{
				pupil.SetFirstName("Alexander");
				REQUIRE(pupil.GetFirstName() == "Alexander");
			}

			THEN("allow set last name")
			{
				pupil.SetLastName("OVI");
				REQUIRE(pupil.GetLastName() == "OVI");
			}

			THEN("allow set middlename name")
			{
				pupil.SetMiddleName("OVI");
				REQUIRE(pupil.GetMiddleName() == "OVI");
			}

			THEN("allow set address")
			{
				pupil.SetAddress("Washington");
				REQUIRE(pupil.GetAddress() == "Washington");
			}

			THEN("allow set school name")
			{
				pupil.SetSchoolName("Moscow");
				REQUIRE(pupil.GetSchoolName() == "Moscow");
			}

			THEN("allow set class number")
			{
				pupil.SetClassNumber("10d");
				REQUIRE(pupil.GetClassNumber() == "10d");
			}
		}
	}
}

TEST_CASE("CTeacher")
{
	CTeacher teacher("Alex", "Ovechkin", "OVI", "Washington, USA", "shot");

	GIVEN("Initially")
	{
		WHEN("Initially")
		{
			THEN("allow get first name")
			{
				REQUIRE(teacher.GetFirstName() == "Alex");
			}

			THEN("allow get last name")
			{
				REQUIRE(teacher.GetLastName() == "Ovechkin");
			}

			THEN("allow get middlename name")
			{
				REQUIRE(teacher.GetMiddleName() == "OVI");
			}

			THEN("allow get address")
			{
				REQUIRE(teacher.GetAddress() == "Washington, USA");
			}

			THEN("allow get subject name")
			{
				REQUIRE(teacher.GetSubjectName() == "shot");
			}
		}

		WHEN("set new value")
		{
			THEN("allow set first name")
			{
				teacher.SetFirstName("Alexander");
				REQUIRE(teacher.GetFirstName() == "Alexander");
			}

			THEN("allow set last name")
			{
				teacher.SetLastName("OVI");
				REQUIRE(teacher.GetLastName() == "OVI");
			}

			THEN("allow set middlename name")
			{
				teacher.SetMiddleName("OVI");
				REQUIRE(teacher.GetMiddleName() == "OVI");
			}

			THEN("allow set address")
			{
				teacher.SetAddress("Washington");
				REQUIRE(teacher.GetAddress() == "Washington");
			}

			THEN("allow set subject name")
			{
				teacher.SetSubjectName("hit");
				REQUIRE(teacher.GetSubjectName() == "hit");
			}
		}
	}
}

TEST_CASE("CWorker")
{
	CWorker worker("Alex", "Ovechkin", "OVI", "Washington, USA", "hockey player");

	GIVEN("Initially")
	{
		WHEN("Initially")
		{
			THEN("allow get first name")
			{
				REQUIRE(worker.GetFirstName() == "Alex");
			}

			THEN("allow get last name")
			{
				REQUIRE(worker.GetLastName() == "Ovechkin");
			}

			THEN("allow get middlename name")
			{
				REQUIRE(worker.GetMiddleName() == "OVI");
			}

			THEN("allow get address")
			{
				REQUIRE(worker.GetAddress() == "Washington, USA");
			}

			THEN("allow get speciality")
			{
				REQUIRE(worker.GetSpeciality() == "hockey player");
			}
		}

		WHEN("set new value")
		{
			THEN("allow set first name")
			{
				worker.SetFirstName("Alexander");
				REQUIRE(worker.GetFirstName() == "Alexander");
			}

			THEN("allow set last name")
			{
				worker.SetLastName("OVI");
				REQUIRE(worker.GetLastName() == "OVI");
			}

			THEN("allow set middlename name")
			{
				worker.SetMiddleName("OVI");
				REQUIRE(worker.GetMiddleName() == "OVI");
			}

			THEN("allow set address")
			{
				worker.SetAddress("Washington");
				REQUIRE(worker.GetAddress() == "Washington");
			}

			THEN("allow set speciality")
			{
				worker.SetSpeciality("forward");
				REQUIRE(worker.GetSpeciality() == "forward");
			}
		}
	}
}

TEST_CASE("CStudent")
{
	CStudent student("Alex", "Ovechkin", "OVI", "Washington, USA", "hockey player", "8");

	GIVEN("Initially")
	{
		WHEN("Initially")
		{
			THEN("allow get first name")
			{
				REQUIRE(student.GetFirstName() == "Alex");
			}

			THEN("allow get last name")
			{
				REQUIRE(student.GetLastName() == "Ovechkin");
			}

			THEN("allow get middlename name")
			{
				REQUIRE(student.GetMiddleName() == "OVI");
			}

			THEN("allow get address")
			{
				REQUIRE(student.GetAddress() == "Washington, USA");
			}

			THEN("allow get high school name")
			{
				REQUIRE(student.GetHighSchoolName() == "hockey player");
			}

			THEN("allow get student card number")
			{
				REQUIRE(student.GetStudentCardNumber() == "8");
			}
		}

		WHEN("set new value")
		{
			THEN("allow set first name")
			{
				student.SetFirstName("Alexander");
				REQUIRE(student.GetFirstName() == "Alexander");
			}

			THEN("allow set last name")
			{
				student.SetLastName("OVI");
				REQUIRE(student.GetLastName() == "OVI");
			}

			THEN("allow set middlename name")
			{
				student.SetMiddleName("OVI");
				REQUIRE(student.GetMiddleName() == "OVI");
			}

			THEN("allow set address")
			{
				student.SetAddress("Washington");
				REQUIRE(student.GetAddress() == "Washington");
			}

			THEN("allow set high school name")
			{
				student.SetHighSchoolName("Washington");
				REQUIRE(student.GetHighSchoolName() == "Washington");
			}

			THEN("allow set student card number")
			{
				student.SetStudentCardNumber("12");
				REQUIRE(student.GetStudentCardNumber() == "12");
			}
		}
	}
}

TEST_CASE("CAdvancedStudent")
{
	CAdvancedStudent student("Alex", "Ovechkin", "OVI", "Washington, USA", "shot", "8", "How to win the Stanley Cup after 13 years on NHL?");

	GIVEN("Initially")
	{
		WHEN("Initially")
		{
			THEN("allow get first name")
			{
				REQUIRE(student.GetFirstName() == "Alex");
			}

			THEN("allow get last name")
			{
				REQUIRE(student.GetLastName() == "Ovechkin");
			}

			THEN("allow get middlename name")
			{
				REQUIRE(student.GetMiddleName() == "OVI");
			}

			THEN("allow get address")
			{
				REQUIRE(student.GetAddress() == "Washington, USA");
			}

			THEN("allow get high school name")
			{
				REQUIRE(student.GetHighSchoolName() == "shot");
			}

			THEN("allow get student card number")
			{
				REQUIRE(student.GetStudentCardNumber() == "8");
			}

			THEN("allow get dissertation topic")
			{
				REQUIRE(student.GetDissertationTopic() == "How to win the Stanley Cup after 13 years on NHL?");
			}
		}

		WHEN("set new value")
		{
			THEN("allow set first name")
			{
				student.SetFirstName("Alexander");
				REQUIRE(student.GetFirstName() == "Alexander");
			}

			THEN("allow set last name")
			{
				student.SetLastName("OVI");
				REQUIRE(student.GetLastName() == "OVI");
			}

			THEN("allow set middlename name")
			{
				student.SetMiddleName("OVI");
				REQUIRE(student.GetMiddleName() == "OVI");
			}

			THEN("allow set address")
			{
				student.SetAddress("Washington");
				REQUIRE(student.GetAddress() == "Washington");
			}

			THEN("allow get high school name")
			{
				student.SetHighSchoolName("shot");
				REQUIRE(student.GetHighSchoolName() == "shot");
			}

			THEN("allow get student card number")
			{
				student.SetStudentCardNumber("12");
				REQUIRE(student.GetStudentCardNumber() == "12");
			}

			THEN("allow get dissertation topic")
			{
				student.SetDissertationTopic("How to pass a pittsburgh penguins");
				REQUIRE(student.GetDissertationTopic() == "How to pass a pittsburgh penguins");
			}
		}
	}
}