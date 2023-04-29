public class Currency {
    public String getCurrencyName(String Code){
        switch(Code){
            case "USD":
                return "US Dollar";
            case "EUR":
                return "Euro";
            case "GBP":
                return "British Pound";
            case "INR":
                return "Indian Rupee";
            case "AUD":
                return "Australian Dollar";
            case "CAD":
                return "Canadian Dollar";
            case "SGD":
                return "Singapore Dollar";
            case "CHF":
                return "Swiss Franc";
            case "MYR":
                return "Malaysian Ringgit";
            case "JPY":
                return "Japanese Yen";
            case "CNY":
                return "Chinese Yuan Renminbi";
            default:
                return "Invalid Currency Code";
        }
    }

    void test(){
        BorwaserTest coverage = new BorwaserTest();
    }
}
