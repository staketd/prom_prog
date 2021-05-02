package ru.fivt.dostavimvse;

import java.io.FileInputStream;
import java.io.IOException;
import java.util.Properties;
import java.util.concurrent.TimeUnit;

import org.junit.AfterClass;
import org.junit.Assert;
import org.junit.BeforeClass;
import org.junit.Test;
import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.firefox.FirefoxDriver;
import org.springframework.boot.test.context.SpringBootTest;
import org.hamcrest.Matchers;

@SpringBootTest
public class FrontendTest {
    private static WebDriver driver;
    private static Properties properties;

    @BeforeClass
    public static void prepareClass() throws IOException {
        FileInputStream fileInputStream = new FileInputStream("src/test/resources/selenium.properties");
        properties = new Properties();
        properties.load(fileInputStream);
        System.setProperty("webdriver.gecko.driver", properties.getProperty("firefoxdriver"));
        driver = new FirefoxDriver();
        driver.manage().window().maximize();
        driver.manage().timeouts().implicitlyWait(10, TimeUnit.SECONDS);
    }

    @Test
    public void testFrontBase() {
        driver.get("http://localhost:8080/create/1");
        WebElement receiver = driver.findElement(By.id("receiver-id"));
        receiver.sendKeys("-1");

        WebElement addProduct = driver.findElement(By.id("add-product-button"));
        WebElement sendOrder = driver.findElement(By.id("send-order"));
        WebElement startVertex = driver.findElement(By.id("start-vertex-id"));
        WebElement endVertex = driver.findElement(By.id("end-vertex-id"));
        WebElement weight = driver.findElement(By.className("weight-input"));
        WebElement price = driver.findElement(By.className("price-input"));

        sendOrder.click();
        expectMessage("No such client or receiver");

        receiver.clear();
        receiver.sendKeys("1");

        sendOrder.click();
        expectMessage("Error happened");

        startVertex.sendKeys("-1");
        endVertex.sendKeys("-2");

        sendOrder.click();
        expectMessage("Error happened");

        startVertex.clear();
        endVertex.clear();

        startVertex.sendKeys("3");
        endVertex.sendKeys("7");

        weight.sendKeys("1");
        price.sendKeys("5");

        sendOrder.click();

        String url = driver.getCurrentUrl();
        Assert.assertThat(url, Matchers.matchesPattern("http://localhost:8080/order/[0-9]*\\?clientId=1"));
    }

    private void expectMessage(String message) {
        Assert.assertEquals(driver.switchTo().alert().getText(), message);
        driver.switchTo().alert().dismiss();
    }

    @AfterClass
    public static void cleanup() {
        driver.close();
    }
}
