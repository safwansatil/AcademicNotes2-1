-- 12. Recent Active Customers: Made at least 3 rentals in the last 180 days.
-- Combination of DATE math and HAVING.
SELECT customer_id, COUNT(*) AS recent_rentals
FROM rental
WHERE rental_date >= CURRENT_DATE - INTERVAL '180 days'
GROUP BY customer_id
HAVING COUNT(*) >= 3;

-- 13. Weighted Genre Score: Calculate store score based on Comedy (1.5x) and Drama (1.0x).
-- This uses Conditional Aggregation (CASE inside SUM/COUNT).
SELECT 
    i.store_id,
    SUM(CASE WHEN c.name = 'Comedy' THEN 1.5 ELSE 0 END) +
    SUM(CASE WHEN c.name = 'Drama' THEN 1.0 ELSE 0 END) AS genre_score
FROM rental r
JOIN inventory i ON r.inventory_id = i.inventory_id
JOIN film_category fc ON i.film_id = fc.film_id
JOIN category c ON fc.category_id = c.category_id
GROUP BY i.store_id;
