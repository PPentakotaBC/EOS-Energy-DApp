# EOS-Energy-DApp
<h1>EOS Energy Trading DApp <h1>

<h2>Setup EOS</h2>
<h3>Install binaries</h3>
brew tap eosio/eosio
brew install eosio
sudo chown -R $(whoami) $(brew --prefix)/*

<h2>Configuring node<h2>
  <h3>Start KEOSD</h3>
    keosd &
  <h3>Start nodeo</h3>
    nodeos -e -p eosio \
    --plugin eosio::producer_plugin \
    --plugin eosio::chain_api_plugin \
    --plugin eosio::http_plugin \
    --access-control-allow-origin='*' \
    --contracts-console \
    --http-validate-host=false \
    --delete-all-blocks \
    --verbose-http-errors >> nodeos.log 2>&1 &
  
<h2>Verify Config</h2>
  tail -f nodeos.log<br/>
  cleos wallet list<br/>
  browse http://localhost:8888/v1/chain/get_info<br/>
  
 <h2>Install EOSIO</h2>
  brew tap eosio/eosio.cdt
  brew install eosio.cdt
  git clone --recursive https://github.com/eosio/eosio.cdt --branch v1.6.1 --single-branch
  cd eosio.cdt<br/>
  ./build.sh<br/>
  sudo ./install.sh<br/>
 
 <h2>Developement Wallet Creation</h2>
   <h3>Create a wallet</h3>
   cleos wallet create --to-console //save the password once generated.
   
   cleos wallet list //For list of wallets<br/>
   cleos wallet unlock //To unlock the wallet<br/>
   cleos wallet create_key //Create development public key for the wallet<br/>
   cleos wallet import //eosio account key<br/>
  
 <h2>Create 3 accounts 1 energyTrade, 1 Pradeep, 1 Prasun account</h2>
    cleos create account eosio energytrade EOS88AeQo5gkvvj1YfDqQAgvyzvyUVHioKL6vuPKSHbnvSDkzwFCk<br/>
    cleos create account eosio pradeep EOS88AeQo5gkvvj1YfDqQAgvyzvyUVHioKL6vuPKSHbnvSDkzwFCk<br/>
    cleos create account eosio prasun EOS88AeQo5gkvvj1YfDqQAgvyzvyUVHioKL6vuPKSHbnvSDkzwFCk<br/>
  
 <h1>Running Energy Trade Application</h1>
    Clone the https://github.com/PPentakotaBC/EOS-Energy-DApp.git repo
    <h2>Compile the energytrade.cpp file</h2>
      eosio-cpp --abigen energytrade.cpp -o energytrade.wasm
      It will generate the WebAssembly virtual machine needed to execute the energytrade smart contract code.
    <h2>Create or Update the contract to the account</h2>
      cleos set contract energytrade ./ -p energytrade@active
     <h2>Register the Energy Meters</h2>
       <h3>Register energytrade account</h3>
        cleos push action energytrade regmeter '["energytrade", "Energy Trade", "Solar panel city, Hyderabad, Telangana", 10000, 0, 0]' -p energytrade@active --json
       <h3>Register pradeep user account</h3>
        cleos push action energytrade regmeter '["pradeep", "Pradeep Pentakota", "Hi-Tech City, Hyderabad, Telangana", 0, 0, 0]' -p energytrade@active --json
       <h3>Register prasun user account</h3>
        cleos push action energytrade regmeter '["prasun", "Prasun Anand", "E-City, Bangalore, Karnataka", 0, 0, 0]' -p energytrade@active --json
      <h2>Transfer Energy Units</h2>
        <h3>Transfer 500 Energy Units from energytrade account to prasun account</h3>
          cleos push action energytrade transfer '["energytrade", "prasun", 500 ]' -p energytrade@active -p pradeep@active -p prasun@active
        <h3>Transfer 1000 Energy Units from energytrade account to prasun account</h3>
          cleos push action energytrade transfer '["energytrade", "prasun", 500 ]' -p energytrade@active -p pradeep@active -p prasun@active
      <h2>Monitor Energy Units</h2>
        cleos push action energytrade eumonitor '["energytrade", "prasun", 500 ]' -p energytrade@active -p pradeep@active -p prasun@active<br/>
        cleos push action energytrade eumonitor '["energytrade", "pradeep", 500 ]' -p energytrade@active -p pradeep@active -p prasun@active
