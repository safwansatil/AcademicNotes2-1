-- 1. Category Popularity: List all categories and total films in each.
-- We join film -> film_category -> category to link titles with their genre names.
SELECT c.name, COUNT(fc.film_id) AS total_films
FROM category c
JOIN film_category fc ON c.category_id = fc.category_id
GROUP BY c.name
ORDER BY total_films DESC;

-- 2. Short Films Search: Titles < 60 min and rental rate of 0.99.
-- Simple filtering using multiple conditions in WHERE.
SELECT title
FROM film
WHERE length < 60 AND rental_rate = 0.99;

-- 3. Staff Performance: Staff names and total rentals processed.
-- Join staff to rental and group by staff identification.
SELECT s.first_name, s.last_name, COUNT(r.rental_id) AS rentals_processed
FROM staff s
JOIN rental r ON s.staff_id = r.staff_id
GROUP BY s.staff_id, s.first_name, s.last_name;

-- 4. Member City: Customer name and their city.
-- Requires walking the FK chain: customer -> address -> city.
SELECT cu.first_name, cu.last_name, ci.city
FROM customer cu
JOIN address a ON cu.address_id = a.address_id
JOIN city ci ON a.city_id = ci.city_id;

-- 5. Rating Counts: Count films per rating with replacement cost between 15 and 20.
-- Aggregation with a pre-filter (WHERE).
SELECT rating, COUNT(*) AS film_count
FROM film
WHERE replacement_cost BETWEEN 15 AND 20
GROUP BY rating;
