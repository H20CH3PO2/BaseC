#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include <string>

#include "Complex.c"

namespace TestDataTypes
{
	#define PATH_LOAD ""


	TEST_CLASS(TestDouble)
	{
	public:
		std::string loadDoubleStirng(const char* path)
		{
			return "1.5";
		}
		double real = 0.0;
		std::string real_string = "";
		double tolerance = 0.000001;
		Double* var;
		TestDouble() 
		{
			real_string = loadDoubleStirng(PATH_LOAD);
			char* end_ptr = NULL;
			real = std::strtold(real_string.c_str(), &end_ptr);
			var = createDouble(real);
		}
		~TestDouble()
		{
			freeDouble(var);
		}
		TEST_METHOD(TestCreateDouble)
		{
			Assert::IsTrue(var != NULL);
			Assert::AreEqual(real, var->data, tolerance);
		}
		TEST_METHOD(TestCopyDouble)
		{
			Double* var2 = copyDouble(var);

			Assert::AreEqual(var->data, var2->data, tolerance);

			freeDouble(var2);
		}
		TEST_METHOD(TestToStringMethodDouble)
		{
			char* actual = toStringDouble(var);

			Assert::IsTrue(strcmp(actual, TYPE_NAME_DOUBLE) == 0);

			free(actual);
		}
		TEST_METHOD(TestDumpMethodDouble)
		{
			char* actual = dumpDouble(var);
			char* expect = concatenateStringsWithSeparator(TYPE_NAME_DOUBLE, (char*)real_string.c_str(), " ");

			size_t minLenght = MIN(strlen(actual), strlen(expect));
			size_t minUpperBound = minLenght - 1;
			Logger::WriteMessage(std::to_string(minLenght).c_str());

			Assert::IsTrue(stringCompareToIndex(actual, expect, minUpperBound));

			free(actual);
			free(expect);
		}
	};

	TEST_CLASS(TestComplex)
	{
	public:
		std::string loadComplexStirng(const char* path)
		{
			return "1.5 2.4";
		}
		double real = 0.0;
		double imaginary = 0.0;
		std::string complex_string = "";
		double tolerance = 0.000001;
		Complex* var;
		TestComplex()
		{
			complex_string = loadComplexStirng(PATH_LOAD);
			char* end_ptr = NULL;
			real = std::strtold(complex_string.c_str(), &end_ptr);
			end_ptr++; // avoid one space
			imaginary = std::strtold(end_ptr, &end_ptr);
			var = createComplex(real, imaginary);
		}
		~TestComplex()
		{
			freeComplex(var);
		}
		TEST_METHOD(TestCreateComplex)
		{
			Assert::IsTrue(var != NULL);

			Assert::AreEqual(real, var->real->data, tolerance);
			Assert::AreEqual(imaginary, var->imaginary->data, tolerance);
		}
		TEST_METHOD(TestCopyComplex)
		{
			Complex* var2 = copyComplex(var);

			Assert::AreEqual(var->real->data, var2->real->data, tolerance);
			Assert::AreEqual(var->imaginary->data, var2->imaginary->data, tolerance);

			freeComplex(var2);
		}
		TEST_METHOD(TestToStringMethodComplex)
		{
			char* actual = toStringComplex(var);

			Assert::IsTrue(strcmp(actual, TYPE_NAME_COMPLEX) == 0);

			free(actual);
		}
		TEST_METHOD(TestDumpMethodComplex)
		{
			char* actual = dumpComplex(var);
			std::string expect = std::string(TYPE_NAME_COMPLEX) + " ";
			expect += std::string(REAL_PART) + " ";
			expect += std::string(dumpDouble(var->real)) + " ";
			expect += std::string(IMAGINARY_PART) + " ";
			expect += std::string(dumpDouble(var->imaginary));

			Logger::WriteMessage(actual);
			Logger::WriteMessage("\n");
			Logger::WriteMessage(expect.c_str());
			Logger::WriteMessage("\n");

			size_t minLenght = MIN(strlen(actual), strlen(expect.c_str()));
			size_t minUpperBound = minLenght - 1;
			Logger::WriteMessage(std::to_string(minLenght).c_str());

			Assert::IsTrue(stringCompareToIndex(actual, expect.c_str(), minUpperBound));

			free(actual);
		}
	};
}