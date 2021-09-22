# 运行fabric



## 使用docker

1. 下载docker镜像

   ```sh
   docker pull hyperledger/cactus-fabric2-all-in-one
   ```

2. 运行

   1. 运行1.4版本及以上

      ```sh
      docker exec -it --workdir /fabric-samples/fabcar/ dindy docker exec cli peer chaincode query --channelID mychannel --name fabcar --ctor '{"Args": [], "Function": "queryAllCars"}'
      [{"Key":"CAR0", "Record":{"colour":"blue","make":"Toyota","model":"Prius","owner":"Tom"}},{"Key":"CAR1", "Record":{"colour":"red","make":"Ford","model":"Mustang","owner":"Brad"}},{"Key":"CAR2", "Record":{"colour":"green","make":"Hyundai","model":"Tucson","owner":"Jin Soo"}},{"Key":"CAR3", "Record":{"colour":"yellow","make":"Volkswagen","model":"Passat","owner":"Max"}},{"Key":"CAR4", "Record":{"colour":"black","make":"Tesla","model":"S","owner":"Adriana"}},{"Key":"CAR5", "Record":{"colour":"purple","make":"Peugeot","model":"205","owner":"Michel"}},{"Key":"CAR6", "Record":{"colour":"white","make":"Chery","model":"S22L","owner":"Aarav"}},{"Key":"CAR7", "Record":{"colour":"violet","make":"Fiat","model":"Punto","owner":"Pari"}},{"Key":"CAR8", "Record":{"colour":"indigo","make":"Tata","model":"Nano","owner":"Valeria"}},{"Key":"CAR9", "Record":{"colour":"brown","make":"Holden","model":"Barina","owner":"Shotaro"}}]
      ```

   2. 运行2.0版本及以上

      ```sh
      cd /fabric-samples/test-network
      export PATH=${PWD}/../bin:${PWD}:$PATH
      export FABRIC_CFG_PATH=$PWD/../config/
      export CORE_PEER_TLS_ENABLED=true
      export CORE_PEER_LOCALMSPID="Org1MSP"
      export CORE_PEER_TLS_ROOTCERT_FILE=${PWD}/organizations/peerOrganizations/org1.example.com/peers/peer0.org1.example.com/tls/ca.crt
      export CORE_PEER_MSPCONFIGPATH=${PWD}/organizations/peerOrganizations/org1.example.com/users/Admin@org1.example.com/msp
      export CORE_PEER_ADDRESS=localhost:7051
      peer chaincode query --channelID mychannel --name fabcar --ctor '{"Args": [], "Function": "queryAllCars"}'
      [{"Key":"CAR0","Record":{"make":"Toyota","model":"Prius","colour":"blue","owner":"Tom"}},{"Key":"CAR1","Record":{"make":"Ford","model":"Mustang","colour":"red","owner":"Brad"}},{"Key":"CAR2","Record":{"make":"Hyundai","model":"Tucson","colour":"green","owner":"Jin Soo"}},{"Key":"CAR277","Record":{"make":"Trabant","model":"601","colour":"Blue","owner":"4cf0a45d-1349-4900-927c-d03e2a2c4dfc"}},{"Key":"CAR3","Record":{"make":"Volkswagen","model":"Passat","colour":"yellow","owner":"Max"}},{"Key":"CAR4","Record":{"make":"Tesla","model":"S","colour":"black","owner":"Adriana"}},{"Key":"CAR5","Record":{"make":"Peugeot","model":"205","colour":"purple","owner":"Michel"}},{"Key":"CAR6","Record":{"make":"Chery","model":"S22L","colour":"white","owner":"Aarav"}},{"Key":"CAR7","Record":{"make":"Fiat","model":"Punto","colour":"violet","owner":"Pari"}},{"Key":"CAR8","Record":{"make":"Tata","model":"Nano","colour":"indigo","owner":"Valeria"}},{"Key":"CAR9","Record":{"make":"Holden","model":"Barina","colour":"brown","owner":"Shotaro"}}]
      Docker Pull Command
      docker pull hyperledger/cactus-fabric2-all-in-one
      Owner
      profile
      hyperledger
      Source Repository
      Github
      hyperledger/cactus
      ```

      