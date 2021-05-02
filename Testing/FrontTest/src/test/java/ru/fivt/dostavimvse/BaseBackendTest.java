package ru.fivt.dostavimvse;

import java.util.Set;

import org.hibernate.Query;
import org.hibernate.Session;
import org.junit.AfterClass;
import org.junit.BeforeClass;
import ru.fivt.dostavimvse.models.Leg;
import ru.fivt.dostavimvse.models.LegType;
import ru.fivt.dostavimvse.models.RouteLeg;

public class BaseBackendTest {
    protected static Session session;

    @BeforeClass
    public static void createSession() {
        session = HibernateSessionFactory.getSessionFactory().openSession();
        session.beginTransaction();
        addTwoWayLeg(session, getLegWithEnds(1, 0).withBasePrice(3.).withSendTime(3));
        addTwoWayLeg(session, getLegWithEnds(1, 2).withBasePrice(1.).withSendTime(1));
        addTwoWayLeg(session, getLegWithEnds(2, 3).withBasePrice(2.).withSendTime(2));
        addTwoWayLeg(session, getLegWithEnds(1, 3).withBasePrice(4.).withSendTime(4));
        addTwoWayLeg(session, getLegWithEnds(0, 3).withBasePrice(7.).withSendTime(7));
        addTwoWayLeg(session, getLegWithEnds(3, 4).withBasePrice(3.).withSendTime(3));
        addTwoWayLeg(session, getLegWithEnds(0, 4).withBasePrice(8.).withSendTime(8));
        addTwoWayLeg(session, getLegWithEnds(0, 2).withBasePrice(1.).withSendTime(1).withMaxWeight(1.));
        session.getTransaction().commit();
    }

    protected static Leg getLegWithEnds(Integer start, Integer end) {
        Leg result = new Leg();
        result.setStartVertex(start);
        result.setEndVertex(end);
        result.setBasePrice(0.1);
        result.setLegType(LegType.TRAIN);
        result.setMaxWeight(100.);
        return result;
    }

    protected Integer countTime(Set<RouteLeg> route) {
        Integer result = 0;
        for (RouteLeg leg : route) {
            result += leg.getLeg().getSendTime();
        }
        return result;
    }

    protected Double countPrice(Set<RouteLeg> route) {
        Double result = 0.;
        for (RouteLeg leg : route) {
            result += leg.getLeg().getBasePrice();
        }
        return result;
    }

    @AfterClass
    public static void cleanUp() {
        session.beginTransaction();
        Query query = session.createQuery("DELETE FROM Leg");
        query.executeUpdate();
        session.getTransaction().commit();
    }

    private static void addTwoWayLeg(Session session, Leg leg) {
        session.save(leg);
        int startVertex = leg.getStartVertex();
        int endVertex = leg.getEndVertex();
        Leg leg2 = new Leg()
                .withLegType(leg.getLegType())
                .withBasePrice(leg.getBasePrice())
                .withEndVertex(startVertex)
                .withStartVertex(endVertex)
                .withSendTime(leg.getSendTime())
                .withMaxWeight(leg.getMaxWeight());
        session.save(leg2);
    }
}
