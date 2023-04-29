public class CurrencyChanger {
    public float currencyChanger(String fromCurrency , String toCurrency , float Amount){
        float result = 0;
        if(fromCurrency.equals("USD") && toCurrency.equals("JOD")){
            result = Amount * 0.71f;
        }else if(fromCurrency.equals("JOD") && toCurrency.equals("USD")){
            result = Amount * 1.41f;
        }else if(fromCurrency.equals("USD") && toCurrency.equals("EUR")){
            result = Amount * 0.84f;
        }else if(fromCurrency.equals("EUR") && toCurrency.equals("USD")){
            result = Amount * 1.19f;
        }else if(fromCurrency.equals("EUR") && toCurrency.equals("JOD")){
            result = Amount * 0.84f;
        }else if(fromCurrency.equals("JOD") && toCurrency.equals("EUR")){
            result = Amount * 1.19f;
        }else if(fromCurrency.equals("USD") && toCurrency.equals("USD")){
            result = Amount;
        }else if(fromCurrency.equals("EUR") && toCurrency.equals("EUR")){
            result = Amount;
        }else if(fromCurrency.equals("JOD") && toCurrency.equals("JOD")){
            result = Amount;
        }
        return result;
    }
}
