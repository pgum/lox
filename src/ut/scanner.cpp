#include "catch.hpp"
#include <scanner.hpp>
namespace UT{
namespace Scanner{

Lox::Scanner sut;

void CheckNoErrors(const Lox::ScannerOutput& so){
  if(so.errors.size() != 0) for(const auto& e : so.errors) std::cout << e << "\n";
  CHECK(so.errors == Lox::ScannerOutput().errors);
}

TEST_CASE("Erroreus", "[Scanner][Edgecase][Error]"){
  Lox::Input invalid_command = "$";
  auto out = sut.scan(invalid_command);
  REQUIRE(out.errors.empty() == false);
  Lox::Lexems expected ={ "\0" };
  REQUIRE(out.lexems == expected);
}

TEST_CASE("Empty input", "[Scanner][Edgecase][Empty]"){
  Lox::Input command = "";
  auto out = sut.scan(command);
  CheckNoErrors(out);
  Lox::Lexems expected ={ "\0" };
  REQUIRE(out.lexems == expected);
}

TEST_CASE("Single and double character operators", "[Scanner][Single][Operator]"){
  Lox::Lexems commands = {"(", ")", "{", "}", "[", "]", ",", ".", ";", ":", "/", "*",
                   "!", "=", ">", "<", "==", "!=", ">=", "<=", "->", "-", "+"};
  for(auto const& c: commands){
    auto out = sut.scan(c);
    CheckNoErrors(out);
    Lox::Lexems expected ={ c, "\0" };
    REQUIRE(out.lexems == expected);
  }
}

TEST_CASE("raw comments //", "[Scanner][Comments]"){
  Lox::Input command = "//This is pretty nice comment!";
  auto out = sut.scan(command);
  CheckNoErrors(out);
  Lox::Lexems expected ={ "//This is pretty nice comment!", "\0" };
  REQUIRE(out.lexems == expected);
}

TEST_CASE("whitespaces", "[Scanner][Whitespaces]"){
  Lox::Input command = "1.2 22\t33   44\n\n55 \t \t \t helo";
  auto out = sut.scan(command);
  CheckNoErrors(out);
  Lox::Lexems expected ={ "1.2", "22", "33", "44", "55", "helo", "\0" };
  REQUIRE(out.lexems == expected);
}

TEST_CASE("//short comment", "[Scanner][Comments]"){
  Lox::Input command = "//helo!\n//comment";
  auto out = sut.scan(command);
  CheckNoErrors(out);
  Lox::Lexems expected ={ "//helo!", "//comment", "\0" };
  REQUIRE(out.lexems == expected);
}

TEST_CASE("numbers - positive integer 1.2.", "[Scanner][Numbers][Integer][Positive]"){
  Lox::Input command = "1.2.";
  auto out = sut.scan(command);
  CheckNoErrors(out);
  Lox::Lexems expected ={ "1.2", "." , "\0" };
  REQUIRE(out.lexems == expected);
}

TEST_CASE("numbers - positive integer 1.2.3", "[Scanner][Numbers][Integer][Positive]"){
  Lox::Input command = "1.2.3";
  auto out = sut.scan(command);
  CheckNoErrors(out);
  Lox::Lexems expected ={ "1.2", ".", "3", "\0" };
  REQUIRE(out.lexems == expected);
}

TEST_CASE("numbers - positive integer 12", "[Scanner][Numbers][Integer][Positive]"){
  Lox::Input command = "12";
  auto out = sut.scan(command);
  CheckNoErrors(out);
  Lox::Lexems expected ={ "12", "\0" };
  REQUIRE(out.lexems == expected);
}

TEST_CASE("numbers - positive integer", "[Scanner][Numbers][Integer][Positive]"){
  Lox::Input command = "123";
  auto out = sut.scan(command);
  CheckNoErrors(out);
  Lox::Lexems expected ={ "123", "\0" };
  REQUIRE(out.lexems == expected);
}

TEST_CASE("numbers - negative integer", "[Scanner][Numbers][Integer][Negative]"){
  Lox::Input command = "-123";
  auto out = sut.scan(command);
  CheckNoErrors(out);
  Lox::Lexems expected ={ "-123", "\0" };
  REQUIRE(out.lexems == expected);
}

TEST_CASE("numbers - positive floats", "[Scanner][Numbers][Float][Positive]"){
  Lox::Input command = "12.3";
  auto out = sut.scan(command);
  CheckNoErrors(out);
  Lox::Lexems expected ={"12.3","\0" };
  REQUIRE(out.lexems == expected);
}

TEST_CASE("numbers - negative floats", "[Scanner][Numbers][Float][Negative]"){
  Lox::Input command = "-12.3";
  auto out = sut.scan(command);
  CheckNoErrors(out);
  Lox::Lexems expected ={"-12.3","\0" };
  REQUIRE(out.lexems == expected);
}

TEST_CASE("numbers - not a number: -.", "[Scanner][Operator][Numbers]"){
  Lox::Input command = "-.";
  auto out = sut.scan(command);
  CheckNoErrors(out);
  Lox::Lexems expected ={ "-", ".", "\0" };
  REQUIRE(out.lexems == expected);
}

TEST_CASE("numbers - not a number: 1..", "[Scanner][Numbers]"){
  Lox::Input command = "1..";
  auto out = sut.scan(command);
  CheckNoErrors(out);
  Lox::Lexems expected ={ "1", ".", ".", "\0" };
  REQUIRE(out.lexems == expected);
}

TEST_CASE("Mixed input", "[Scanner][Sanity]"){
  Lox::Input command = "{1}=0//helo !";
  auto out = sut.scan(command);
  CheckNoErrors(out);
  Lox::Lexems expected ={ "{", "1", "}", "=", "0", "//helo !", "\0" };
  REQUIRE(out.lexems == expected);
}

TEST_CASE("Mixed input2", "[Scanner][Sanity]"){
  Lox::Input command = "asdf(){return 1==0;}; //helo !";
  auto out = sut.scan(command);
  CheckNoErrors(out);
  Lox::Lexems expected ={ "asdf", "(", ")", "{", "return", "1", "==", "0", ";", "}", ";", "//helo !", "\0" };
  REQUIRE(out.lexems == expected);
}

TEST_CASE("Mixed input2.1", "[Scanner][Sanity]"){
  Lox::Input command = "identifier!";
  auto out = sut.scan(command);
  CheckNoErrors(out);
  Lox::Lexems expected ={ "identifier", "!", "\0" };
  REQUIRE(out.lexems == expected);
}

TEST_CASE("Mixed input3", "[Scanner][Sanity]"){
  Lox::Input command = "asdf\nddd\n123\nqwe2";
  auto out = sut.scan(command);
  CheckNoErrors(out);
  Lox::Lexems expected ={ "asdf", "ddd", "123", "qwe2", "\0" };
  REQUIRE(out.lexems == expected);
}

TEST_CASE("Simple empty string", "[Scanner][Empty][String]"){
  Lox::Input command = "\"\"";
  auto out = sut.scan(command);
  CheckNoErrors(out);
  Lox::Lexems expected ={ "\"\"", "\0" };
  REQUIRE(out.lexems == expected);
}

TEST_CASE("Simple nonempty string", "[Scanner][Filled][String]"){
  Lox::Input command = "\"hello\"";
  auto out = sut.scan(command);
  CheckNoErrors(out);
  Lox::Lexems expected ={ "\"hello\"", "\0" };
  REQUIRE(out.lexems == expected);
}

TEST_CASE("String with numbers", "[Scanner][String][Numbers]"){
  Lox::Input command = "2 \"hello\" 6";
  auto out = sut.scan(command);
  CheckNoErrors(out);
  Lox::Lexems expected ={ "2", "\"hello\"", "6", "\0" };
  REQUIRE(out.lexems == expected);
}

TEST_CASE("Identifier short", "[Scanner][Identifier]"){
  Lox::Input command = "id";
  auto out = sut.scan(command);
  CheckNoErrors(out);
  Lox::Lexems expected ={ "id", "\0" };
  REQUIRE(out.lexems == expected);
}

TEST_CASE("Identifier long", "[Scanner][Identifier]"){
  Lox::Input command = "commonId";
  auto out = sut.scan(command);
  CheckNoErrors(out);
  Lox::Lexems expected ={ "commonId", "\0" };
  REQUIRE(out.lexems == expected);
}

}//namespace Scanner
}//namespace UT
