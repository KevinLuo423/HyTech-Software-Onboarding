#include <iostream>
#include <fstream>
#include <string>
#include "addressbook.pb.h"

using namespace std;

// Iterates though all people in the AddressBook and prints info about them.
void ListPeople(const Lab3::AddressBook& address_book) {
  for (const Lab3::Person& person : address_book.people()) {
    cout << "Person ID: " << person.id() << endl;
    cout << "  Name: " << person.name() << endl;
    cout << "  E-mail address: " << person.email() << endl;

    for (const Lab3::Person::PhoneNumber& phone_number : person.phones()) {
      switch (phone_number.type()) {
        case Lab3::Person::PHONE_TYPE_MOBILE:
          cout << "  Mobile phone #: ";
          break;
        case Lab3::Person::PHONE_TYPE_HOME:
          cout << "  Home phone #: ";
          break;
        case Lab3::Person::PHONE_TYPE_WORK:
          cout << "  Work phone #: ";
          break;
        case Lab3::Person::PHONE_TYPE_UNSPECIFIED:
        default:
          cout << "  Phone #: ";
          break;
      }
      cout << phone_number.number() << endl;
    }
  }
}

// Main function:  Reads the entire address book from a file and prints all
//   the information inside.
int main(int argc, char* argv[]) {
  // Verify that the version of the library that we linked against is
  // compatible with the version of the headers we compiled against.
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  if (argc != 2) {
    cerr << "Usage:  " << argv[0] << " ADDRESS_BOOK_FILE" << endl;
    return -1;
  }

  Lab3::AddressBook address_book;

  {
    // Read the existing address book.
    fstream input(argv[1], ios::in | ios::binary);
    if (!address_book.ParseFromIstream(&input)) {
      cerr << "Failed to parse address book." << endl;
      return -1;
    }
  }

  ListPeople(address_book);

  // Optional:  Delete all global objects allocated by libprotobuf.
  google::protobuf::ShutdownProtobufLibrary();

  return 0;
}
