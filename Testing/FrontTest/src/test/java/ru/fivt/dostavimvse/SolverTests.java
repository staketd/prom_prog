package ru.fivt.dostavimvse;

import java.util.Arrays;
import java.util.Collection;
import java.util.Set;

import org.junit.Assert;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import org.springframework.boot.test.context.SpringBootTest;
import ru.fivt.dostavimvse.models.Order;
import ru.fivt.dostavimvse.models.Product;

@RunWith(Parameterized.class)
@SpringBootTest
public class SolverTests extends BaseBackendTest {

    @Parameterized.Parameter(0)
    public static Integer startVertex;

    @Parameterized.Parameter(1)
    public static Integer endVertex;

    @Parameterized.Parameter(2)
    public static Double expectedResult;

    @Parameterized.Parameters(name = "Начальная вершина: {0}, конечная вершина: {1}, ожидаемый ответ: {2}")
    public static Collection<Object[]> createParameters() {
        return Arrays.asList(new Object[][]{
                {0, 1, 3.},
                {0, 3, 6.},
                {0, 4, 8.},
                {1, 3, 3.},
                {0, 2, 4.}
        });
    }

    @Test
    public void testOptimalSolver() {
        OptimalTimeSolver timeSolver = new OptimalTimeSolver();
        OptimalPriceSolver priceSolver = new OptimalPriceSolver();
        Order testOrder = new Order();
        testOrder.setStartVertex(startVertex);
        testOrder.setEndVertex(endVertex);
        testOrder.setProducts(Set.of(new Product().withWeight(1.5).withPrice(0.)));
        Assert.assertEquals(Integer.valueOf(expectedResult.intValue()), countTime(timeSolver.buildOptimalRoute(testOrder).getRouteLegs()));
        Assert.assertEquals(expectedResult, countPrice(priceSolver.buildOptimalRoute(testOrder).getRouteLegs()));
    }
}
