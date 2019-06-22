#include "catch.hpp"
#include <scanner.hpp>
namespace UT{
namespace Scanner{
using Token= std::string;
using Tokens= std::vector<Token>;
using Munch= std::optional<std::string>;

//using Tokens = std::vector<Lox::Token>;
//using Lexem = Lox::Input;
  Lox::Scanner sut;

void RequireNoError(const Lox::ScannerOutput& so){
  CHECK(so.errors.size() == 0);
  REQUIRE(so.hasErrors() == false);
}

TEST_CASE("Erroreus", "[Scanner][Edgecase][Error]"){
  Lox::Input invalid_command = "$";
  auto out = sut.scan(invalid_command);
  REQUIRE(out.hasErrors() == true);
  Tokens tokens ={ "\0" };
  REQUIRE(out.tokens == tokens);
}

TEST_CASE("Empty input", "[Scanner][Edgecase][Empty]"){
  Lox::Input command = "";
  auto out = sut.scan(command);
  RequireNoError(out);
  Tokens tokens ={ "\0" };
  REQUIRE(out.tokens == tokens);
}

TEST_CASE("Single and double character operators", "[Scanner][Single][Operator]"){
  Tokens tokens = {"(", ")", "{", "}", "[", "]", ",", ".", ";", ":", "/", "*",
                   "!", "=", ">", "<", "==", "!=", ">=", "<=", "->", "-", "+"};
  for(auto const& t: tokens){
    auto out = sut.scan(t);
    RequireNoError(out);
    Tokens tokens ={ t, "\0" };
    REQUIRE(out.tokens == tokens);
  }
}

TEST_CASE("raw comments //", "[Scanner][Long][Comments]"){
  Lox::Input command = "//This is pretty nice comment!";
  auto out = sut.scan(command);
  RequireNoError(out);
  Tokens tokens ={ "//This is pretty nice comment!", "\0" };
  REQUIRE(out.tokens == tokens);
}

TEST_CASE("//short comment", "[Scanner][Short][Comments]"){
  Lox::Input command = "//helo!";
  auto out = sut.scan(command);
  RequireNoError(out);
  Tokens tokens ={ "//helo!", "\0" };
  REQUIRE(out.tokens == tokens);
}

TEST_CASE("comments and other tokens", "[Scanner][Long][Comments]"){
  Lox::Input command = "(){}//This is pretty nice comment!";
  auto out = sut.scan(command);
  RequireNoError(out);
  Tokens tokens = {"(", ")", "{", "}", "//This is pretty nice comment!","\0" };
  REQUIRE(out.tokens == tokens);
}

TEST_CASE("numbers - positive integer 1.2.", "[Scanner][Numbers][Integer][Positive][adbd]"){
  Lox::Input command = "1.2.";
  auto out = sut.scan(command);
  RequireNoError(out);
  Tokens tokens ={ "1.2", "." , "\0" };
  REQUIRE(out.tokens == tokens);
}

TEST_CASE("numbers - positive integer 1.2.3", "[Scanner][Numbers][Integer][Positive][adbdc]"){
  Lox::Input command = "1.2.3";
  auto out = sut.scan(command);
  RequireNoError(out);
  Tokens tokens ={ "1.2", ".", "3", "\0" };
  REQUIRE(out.tokens == tokens);
}

TEST_CASE("numbers - positive integer 12", "[Scanner][Numbers][Integer][Positive][ab]"){
  Lox::Input command = "12";
  auto out = sut.scan(command);
  RequireNoError(out);
  Tokens tokens ={ "12", "\0" };
  REQUIRE(out.tokens == tokens);
}

TEST_CASE("numbers - positive integer", "[Scanner][Numbers][Integer][Positive][abc]"){
  Lox::Input command = "123";
  auto out = sut.scan(command);
  RequireNoError(out);
  Tokens tokens ={ "123", "\0" };
  REQUIRE(out.tokens == tokens);
}

TEST_CASE("numbers - negative integer", "[Scanner][Numbers][Integer][Negative][mabc]"){
  Lox::Input command = "-123";
  auto out = sut.scan(command);
  RequireNoError(out);
  Tokens tokens ={ "-123", "\0" };
  REQUIRE(out.tokens == tokens);
}

TEST_CASE("numbers - positive floats", "[Scanner][Long][Numbers][Float][Positive][abdc]"){
  Lox::Input command = "12.3";
  auto out = sut.scan(command);
  RequireNoError(out);
  Tokens tokens ={"12.3","\0" };
  REQUIRE(out.tokens == tokens);
}

TEST_CASE("numbers - negative floats", "[Scanner][Long][Numbers][Float][Negative][mabdc]"){
  Lox::Input command = "-12.3";
  auto out = sut.scan(command);
  RequireNoError(out);
  Tokens tokens ={"-12.3","\0" };
  REQUIRE(out.tokens == tokens);
}

TEST_CASE("numbers - not a number: -.", "[Scanner][Numbers][Not][md]"){
  Lox::Input command = "-.";
  auto out = sut.scan(command);
  RequireNoError(out);
  Tokens tokens ={ "-", ".", "\0" };
  REQUIRE(out.tokens == tokens);
}

TEST_CASE("numbers - not a number: 1..", "[Scanner][Numbers][Not][add]"){
  Lox::Input command = "1..";
  auto out = sut.scan(command);
  RequireNoError(out);
  Tokens tokens ={ "1", ".", ".", "\0" };
  REQUIRE(out.tokens == tokens);
}


TEST_CASE("Mixed input", "[Scanner][Sanity]"){
  Lox::Input command = "{1}=0//helo !";
  auto out = sut.scan(command);
  RequireNoError(out);
  Tokens tokens ={ "{", "1", "}", "=", "0", "//helo !","\0" };
  REQUIRE(out.tokens == tokens);
}

}//namespace Scanner
}//namespace UT
