package ru.fivt.dostavimvse;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringJUnit4ClassRunner;
import ru.fivt.dostavimvse.models.Product;

@RunWith(SpringJUnit4ClassRunner.class)
@SpringBootTest
public class DostavimvseApplicationTests extends BaseBackendTest {

	@Test
	public void contextLoads() {
	}


	@Test
	public void checkProductNonNegativePriceCreated() {
        session.beginTransaction();
		Product product = new Product();
		product.setPrice(0.5);
		product.setWeight(0.8);
	}

}
