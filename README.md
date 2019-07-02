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
  tail -f nodeos.log
  cleos wallet list
  browse http://localhost:8888/v1/chain/get_info
  
 <h2>Install EOSIO</h2>
  brew tap eosio/eosio.cdt
  brew install eosio.cdt 
  
 <h2>Developement Wallet Creation</h2>
   <h3>Create a wallet</h3>
   cleos wallet create --to-console //save the password once generated.
   
   cleos wallet list //For list of wallets
   cleos wallet unlock //To unlock the wallet
   cleos wallet create_key //Create development public key for the wallet
   cleos wallet import //eosio account key
  
 <h2>Create 3 accounts 1 energyTrade, 1 Pradeep, 1 Prasun account</h2>
    cleos create account eosio energytrade EOS88AeQo5gkvvj1YfDqQAgvyzvyUVHioKL6vuPKSHbnvSDkzwFCk
    cleos create account eosio pradeep EOS88AeQo5gkvvj1YfDqQAgvyzvyUVHioKL6vuPKSHbnvSDkzwFCk 
    cleos create account eosio prasun EOS88AeQo5gkvvj1YfDqQAgvyzvyUVHioKL6vuPKSHbnvSDkzwFCk
   
 
