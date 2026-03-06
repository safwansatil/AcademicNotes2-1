-- 9. Procedure: Promo Credit
-- This procedure pays for the latest unpaid rental by inserting into the payment table.
-- UNPAID here is defined as a rental without an entry in the payment table.
CREATE OR REPLACE PROCEDURE add_rental_credit(cust_id INT, credit_amount DECIMAL)
LANGUAGE plpgsql AS $$
DECLARE
    v_rental_id INT;
    v_staff_id INT;
BEGIN
    -- Find the latest rental ID that doesn't have a payment yet
    SELECT r.rental_id, r.staff_id INTO v_rental_id, v_staff_id
    FROM rental r
    LEFT JOIN payment p ON r.rental_id = p.rental_id
    WHERE r.customer_id = cust_id AND p.payment_id IS NULL
    ORDER BY r.rental_date DESC
    LIMIT 1;

    -- If found, insert the payment record
    IF FOUND THEN
        INSERT INTO payment (customer_id, staff_id, rental_id, amount, payment_date)
        VALUES (cust_id, v_staff_id, v_rental_id, credit_amount, NOW());
        RAISE NOTICE 'Credit of % applied to rental %', credit_amount, v_rental_id;
    ELSE
        RAISE NOTICE 'No unpaid rentals found for customer %', cust_id;
    END IF;
END $$;

-- 10. Table Function: High Value Inventory
-- Returns a result set (table) based on a threshold.
CREATE OR REPLACE FUNCTION get_expensive_inventory(min_cost DECIMAL) 
RETURNS TABLE(film_title VARCHAR, r_cost DECIMAL, s_id INT) 
LANGUAGE plpgsql AS $$
BEGIN
    RETURN QUERY
    SELECT f.title, f.replacement_cost, i.store_id
    FROM film f
    JOIN inventory i ON f.film_id = i.film_id
    WHERE f.replacement_cost > min_cost;
END $$;

-- 11. Anonymous Block: Rental Status Check
-- Uses a boolean check to determine if ANY copies are available.
DO $$
DECLARE
    v_target_film_id INT := 10; -- Example film ID
    v_copies_available BOOLEAN;
BEGIN
    -- Check if there exists any inventory item for this film that is NOT currently rented
    -- A copy is "available" if it's in inventory and (it has no rental records OR its latest rental has been returned).
    SELECT EXISTS (
        SELECT 1
        FROM inventory i
        WHERE i.film_id = v_target_film_id
        AND NOT EXISTS (
            SELECT 1 FROM rental r 
            WHERE r.inventory_id = i.inventory_id 
            AND r.return_date IS NULL
        )
    ) INTO v_copies_available;

    IF v_copies_available THEN
        RAISE NOTICE 'Copies Available for film ID %', v_target_film_id;
    ELSE
        RAISE NOTICE 'Out of Stock for film ID %', v_target_film_id;
    END IF;
END $$;
