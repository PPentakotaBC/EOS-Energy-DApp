#include <eosio/eosio.hpp>

using namespace eosio;

class [[eosio::contract("energytrade")]] energytrade : public eosio::contract {

public:
  
  energytrade(name receiver, name code,  datastream<const char*> ds): contract(receiver, code, ds) {}

  [[eosio::action]]
  
  void regmeter(name user, std::string full_name, std::string fulladdress, uint64_t eugenerated, uint64_t eutransfer, uint64_t eubalance) {
    address_index addresses( get_self(), get_first_receiver().value );
    auto iterator = addresses.find(user.value);
    //Registering an Energy Meter
    if( iterator == addresses.end() )
    {
      addresses.emplace(user, [&]( auto& row ) {
       row.key = user;
       row.full_name = full_name;
       row.fulladdress = fulladdress;
       row.eugenerated = eugenerated;
       row.eutransfer = eutransfer;
       row.eubalance = eubalance;
      });
      print ( "Energy Meter is registered for ", user );
    }
    else {
    //Updating an Energy Meter
      addresses.modify(iterator, user, [&]( auto& row ) {
        row.key = user;
        row.full_name = full_name;
        row.fulladdress = fulladdress;
        row.eugenerated = eugenerated;
        row.eutransfer = eutransfer;
        row.eubalance = eubalance;
      });
      print ( "Energy Meter is Updated for ", user );
    }
  }

  [[eosio::action]]
  void erase(name user) {
    //Removing table values 
    address_index addresses( get_self(), get_first_receiver().value);
    auto iterator = addresses.find(user.value);
    check(iterator != addresses.end(), "Record does not exist");
    addresses.erase(iterator);
    print ( "Values are deleted from the table" );
  }

  [[eosio::action]]
  void transfer(name from, name to, uint64_t eutransfer) {
    print ( "Transfer of Energy Units is Initiated" );
    //from - Account from where energy is to be transferred, to - Account to where energy is given
    address_index addresses( get_self(), get_first_receiver().value);
    auto iterator = addresses.find(from.value);
    check(iterator != addresses.end(), "Record does not exist");
    auto iterator2 = addresses.find(to.value);
    check(iterator2 != addresses.end(), "Record does not exist");
    addresses.modify(iterator2, to, [&]( auto& row ) {
        row.key = to;
        //add the balance to receiver account
        row.eubalance = row.eubalance + eutransfer;
        print ( "Energy Units is sent or added to the receiver: ", to );
      });
    addresses.modify(iterator, from, [&]( auto& row ) {
        row.key = from;
        //subtract the balance from the giver account
        if(row.eubalance == 0){
          row.eubalance = row.eugenerated - eutransfer;
          row.eugenerated = row.eubalance;
        }
        else{
          row.eubalance = row.eubalance - eutransfer;
        }
        print ( "Energy Units is subtracted from the sender: ", from );
      });
  }

  [[eosio::action]]
  void eumonitor(name from, name to, uint64_t eubalance) {
    //Monitoring of Energy Units consumed
    print ( "Monitor of Energy Units is started " );
    address_index addresses( get_self(), get_first_receiver().value);
    auto iterator = addresses.find(from.value);
    check(iterator != addresses.end(), "Record does not exist");
    auto iterator2 = addresses.find(to.value);
    check(iterator2 != addresses.end(), "Record does not exist");
    addresses.modify(iterator2, to, [&]( auto& row ) {
        row.key = to;
        //add the balance to receiver account
        //row.eubalance = row.eubalance + eutransfer;
        print ( "Energy Units transferred from ",  from, " to ",  to," is ", row.eubalance);
      });
  }

private:
  struct [[eosio::table]] person {
    name key;
    std::string full_name;
    std::string fulladdress;
    uint64_t eugenerated;
    uint64_t eutransfer;
    uint64_t eubalance;
    uint64_t primary_key() const { return key.value; }
  };
  typedef eosio::multi_index<"people"_n, person> address_index;

};    