void cek_Output(int number){
  if(number == 1){
      if(Firebase.getString(firebaseData,"Output/Blower")){
      if(firebaseData.dataType() == "string"){
          String mod = firebaseData.stringData();
          if(mod=="ON"){
           
            Serial.println("Blower On");
            //digitalWrite(D5,HIGH);
           
          }
          else if(mod =="OFF"){
            Serial.println("Blower Off");
            //digitalWrite(D5,LOW);
          }
      }
    }
  }

  else if(number == 2){
      if(Firebase.getString(firebaseData,"Output/Pump")){
      if(firebaseData.dataType() == "string"){
          String mod = firebaseData.stringData();
          if(mod=="ON"){
           
            Serial.println("Pump On");
            //digitalWrite(D5,HIGH);
           
          }
          else if(mod =="OFF"){
            Serial.println("Pump Off");
            //digitalWrite(D5,LOW);
          }
      }
    }
  }

  else if(number == 3){
      if(Firebase.getString(firebaseData,"Output/Selenoid")){
      if(firebaseData.dataType() == "string"){
          String mod = firebaseData.stringData();
          if(mod=="ON"){
           
            Serial.println("Selenoid On");
            //digitalWrite(D5,HIGH);
           
          }
          else if(mod =="OFF"){
            Serial.println("Selenoid Off");
            //digitalWrite(D5,LOW);
          }
      }
    }
  }
  
}
