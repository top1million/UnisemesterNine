public class BorwaserTest {

    public String getCurrency(String code){
        switch(code){
            case "USD":
                return "american dollar";
            case "JOD" :
                return "Jordanian dinar";
            default:
                return "Wrong currency";
        }
    }
}
