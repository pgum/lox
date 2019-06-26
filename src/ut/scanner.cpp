#include "catch.hpp"
#include <scanner.hpp>
namespace UT{
namespace Scanner{

Lox::Scanner sut;

void RequireNoError(const Lox::ScannerOutput& so){
  for(const auto& e : so.errors) std::cout << e << "\n";
  REQUIRE(so.errors.size() == 0);
}

TEST_CASE("Erroreus", "[Scanner][Edgecase][Error]"){
  Lox::Input invalid_command = "$";
  auto out = sut.scan(invalid_command);
  REQUIRE(out.errors.size() == 1);
  Lox::Lexems lexems ={ "\0" };
  REQUIRE(out.lexems == lexems);
}

TEST_CASE("Empty input", "[Scanner][Edgecase][Empty]"){
  Lox::Input command = "";
  auto out = sut.scan(command);
  RequireNoError(out);
  Lox::Lexems lexems ={ "\0" };
  REQUIRE(out.lexems == lexems);
}

TEST_CASE("Single and double character operators", "[Scanner][Single][Operator]"){
  Lox::Lexems lexems = {"(", ")", "{", "}", "[", "]", ",", ".", ";", ":", "/", "*",
                   "!", "=", ">", "<", "==", "!=", ">=", "<=", "->", "-", "+"};
  for(auto const& t: lexems){
    auto out = sut.scan(t);
    RequireNoError(out);
    Lox::Lexems lexems ={ t, "\0" };
    REQUIRE(out.lexems == lexems);
  }
}

TEST_CASE("raw comments //", "[Scanner][Long][Comments]"){
  Lox::Input command = "//This is pretty nice comment!";
  auto out = sut.scan(command);
  RequireNoError(out);
  Lox::Lexems lexems ={ "//This is pretty nice comment!", "\0" };
  REQUIRE(out.lexems == lexems);
}

TEST_CASE("//short comment", "[Scanner][Short][Comments]"){
  Lox::Input command = "//helo!";
  auto out = sut.scan(command);
  RequireNoError(out);
  Lox::Lexems lexems ={ "//helo!", "\0" };
  REQUIRE(out.lexems == lexems);
}

TEST_CASE("comments and other lexems", "[Scanner][Long][Comments]"){
  Lox::Input command = "(){}//This is pretty nice comment!";
  auto out = sut.scan(command);
  RequireNoError(out);
  Lox::Lexems lexems = {"(", ")", "{", "}", "//This is pretty nice comment!","\0" };
  REQUIRE(out.lexems == lexems);
}

TEST_CASE("numbers - positive integer 1.2.", "[Scanner][Numbers][Integer][Positive][adbd]"){
  Lox::Input command = "1.2.";
  auto out = sut.scan(command);
  RequireNoError(out);
  Lox::Lexems lexems ={ "1.2", "." , "\0" };
  REQUIRE(out.lexems == lexems);
}

TEST_CASE("numbers - positive integer 1.2.3", "[Scanner][Numbers][Integer][Positive][adbdc]"){
  Lox::Input command = "1.2.3";
  auto out = sut.scan(command);
  RequireNoError(out);
  Lox::Lexems lexems ={ "1.2", ".", "3", "\0" };
  REQUIRE(out.lexems == lexems);
}

TEST_CASE("numbers - positive integer 12", "[Scanner][Numbers][Integer][Positive][ab]"){
  Lox::Input command = "12";
  auto out = sut.scan(command);
  RequireNoError(out);
  Lox::Lexems lexems ={ "12", "\0" };
  REQUIRE(out.lexems == lexems);
}

TEST_CASE("numbers - positive integer", "[Scanner][Numbers][Integer][Positive][abc]"){
  Lox::Input command = "123";
  auto out = sut.scan(command);
  RequireNoError(out);
  Lox::Lexems lexems ={ "123", "\0" };
  REQUIRE(out.lexems == lexems);
}

TEST_CASE("numbers - negative integer", "[Scanner][Numbers][Integer][Negative][mabc]"){
  Lox::Input command = "-123";
  auto out = sut.scan(command);
  RequireNoError(out);
  Lox::Lexems lexems ={ "-123", "\0" };
  REQUIRE(out.lexems == lexems);
}

TEST_CASE("numbers - positive floats", "[Scanner][Long][Numbers][Float][Positive][abdc]"){
  Lox::Input command = "12.3";
  auto out = sut.scan(command);
  RequireNoError(out);
  Lox::Lexems lexems ={"12.3","\0" };
  REQUIRE(out.lexems == lexems);
}

TEST_CASE("numbers - negative floats", "[Scanner][Long][Numbers][Float][Negative][mabdc]"){
  Lox::Input command = "-12.3";
  auto out = sut.scan(command);
  RequireNoError(out);
  Lox::Lexems lexems ={"-12.3","\0" };
  REQUIRE(out.lexems == lexems);
}

TEST_CASE("numbers - not a number: -.", "[Scanner][Numbers][Not][md]"){
  Lox::Input command = "-.";
  auto out = sut.scan(command);
  RequireNoError(out);
  Lox::Lexems lexems ={ "-", ".", "\0" };
  REQUIRE(out.lexems == lexems);
}

TEST_CASE("numbers - not a number: 1..", "[Scanner][Numbers][Not][add]"){
  Lox::Input command = "1..";
  auto out = sut.scan(command);
  RequireNoError(out);
  Lox::Lexems lexems ={ "1", ".", ".", "\0" };
  REQUIRE(out.lexems == lexems);
}

TEST_CASE("Mixed input", "[Scanner][Sanity]"){
  Lox::Input command = "{1}=0//helo !";
  auto out = sut.scan(command);
  RequireNoError(out);
  Lox::Lexems lexems ={ "{", "1", "}", "=", "0", "//helo !", "\0" };
  REQUIRE(out.lexems == lexems);
}

TEST_CASE("Mixed input2", "[Scanner][Sanity]"){
  Lox::Input command = "asdf(){return 1==0;}; //helo !";
  auto out = sut.scan(command);
  RequireNoError(out);
  Lox::Lexems lexems ={ "asdf", "(", ")", "{", "return", "1", "==", "0", ";", "}", ";", "//helo !", "\0" };
  REQUIRE(out.lexems == lexems);
}

TEST_CASE("Mixed input3", "[Scanner][Sanity]"){
  Lox::Input command = "asdf\nddd\n123\nqwe2";
  auto out = sut.scan(command);
  RequireNoError(out);
  Lox::Lexems lexems ={ "asdf", "ddd", "123", "qwe2", "\0" };
  REQUIRE(out.lexems == lexems);
}

TEST_CASE("Simple empty string", "[Scanner][Empty][String]"){
  Lox::Input command = "\"\"";
  auto out = sut.scan(command);
  RequireNoError(out);
  Lox::Lexems lexems ={ "\"\"", "\0" };
  REQUIRE(out.lexems == lexems);
}

TEST_CASE("Simple nonempty string", "[Scanner][Filled][String]"){
  Lox::Input command = "\"hello\"";
  auto out = sut.scan(command);
  RequireNoError(out);
  Lox::Lexems lexems ={ "\"hello\"", "\0" };
  REQUIRE(out.lexems == lexems);
}

TEST_CASE("String with numbers", "[Scanner][String][Numbers]"){
  Lox::Input command = "2 \"hello\" 6";
  auto out = sut.scan(command);
  RequireNoError(out);
  Lox::Lexems lexems ={ "2", "\"hello\"", "6", "\0" };
  REQUIRE(out.lexems == lexems);
}

TEST_CASE("Identifier short", "[Scanner][Identifier]"){
  Lox::Input command = "id";
  auto out = sut.scan(command);
  RequireNoError(out);
  Lox::Lexems lexems ={ "id", "\0" };
  REQUIRE(out.lexems == lexems);
}

TEST_CASE("Identifier long", "[Scanner][Identifier]"){
  Lox::Input command = "commonId";
  auto out = sut.scan(command);
  RequireNoError(out);
  Lox::Lexems lexems ={ "commonId", "\0" };
  REQUIRE(out.lexems == lexems);
}

}//namespace Scanner
}//namespace UT
