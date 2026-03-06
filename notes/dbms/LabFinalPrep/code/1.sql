-- 1
select f.title, count(DISTINCT r.rental_id) as cnt from film f
left join inventory i on i.film_id = f.film_id
left join rental r on i.inventory_id = r.inventory_id
group by f.title
order by cnt desc
limit 5;

--2
select s.store_id, sum(p.amount) as total_revenue from store s
left join staff st on st.staff_id = s.manager_staff_id
left join paymeny p on p.staff_id = st.staff_id
group by 1;

--3
select f.title, count(DISTINCT ci.city_id) from film
left join inventory i on i.film_id = f.film_id  
left join rental r on r.inventory_id = i.inventory_id
left join customer c on c.customer_id = r.customer_id
left join address a on c.address_id = a.address_id
left join city ci on ci.city_id = a.city_id
group by 1
having count(ci.city_id) > 3;

--4
select * from customer c
left join rental r
where r.customer_id IS NULL;

--5
select c.customer_id, sum(p.amount) from customer c
left join payment p on c.customer_id = p.customer_id
group by 1
having sum(p.amount) > avg(p.amount);


--6
select f.title, count(r.rental_id) from film f
left join inventory i on i.film_id = f.film_id
left join rental r on r.film_id = i.film_id
where 1 like '% %'
and 
group by 1
having count(r.rental_id) >= 20;

--7

select c.first_name, c.last_name, s.store_id,
(sum(p.amount) group by c.first_name, c.last_name / sum(p.amount) GROUP BY s.store_id) * 100
from customer c
left join store s on s.store_id = c.store_id
left join payment p on p.customer_id = c.customer_id
group by c.first_name, c.last_name;


--8

do $$
declare v_customer_id int; cnt int
BEGIN
select count(*) from rental GROUP BY customer_id having customer_id = v_customer_id into cnt;
if cnt > 30 then
raise notice 'freq renter';
else raise notice 'ocasonal renter';
end if;
end $$;





