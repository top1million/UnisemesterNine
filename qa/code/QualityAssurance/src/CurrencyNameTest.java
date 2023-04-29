import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class CurrencyNameTest {
    @Test
    public void testBorwaser(){
        BorwaserTest borwaserTest = new BorwaserTest();
        assertEquals("american dollar", borwaserTest.getCurrency("USD"));
        assertEquals("Jordanian dinar", borwaserTest.getCurrency("JOD"));
        assertEquals("Wrong currency", borwaserTest.getCurrency("EUR"));
    }
    @Test
    public void testCurrencyChanger(){
        CurrencyChanger currencyChanger = new CurrencyChanger();
        assertEquals(0.71f, currencyChanger.currencyChanger("USD", "JOD", 1), 0.01f);
        assertEquals(1.41f, currencyChanger.currencyChanger("JOD", "USD", 1), 0.01f);
        assertEquals(0.84f, currencyChanger.currencyChanger("USD", "EUR", 1), 0.01f);
        assertEquals(1.19f, currencyChanger.currencyChanger("EUR", "USD", 1), 0.01f);
        assertEquals(0.84f, currencyChanger.currencyChanger("EUR", "JOD", 1), 0.01f);
        assertEquals(1.19f, currencyChanger.currencyChanger("JOD", "EUR", 1), 0.01f);
        assertEquals(1, currencyChanger.currencyChanger("USD", "USD", 1), 0.01f);
        assertEquals(1, currencyChanger.currencyChanger("EUR", "EUR", 1), 0.01f);
        assertEquals(1, currencyChanger.currencyChanger("JOD", "JOD", 1), 0.01f);
    }
}


