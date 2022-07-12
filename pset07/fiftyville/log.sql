-- Keep a log of any SQL queries you execute as you solve the mystery.

select description
from crime_scene_reports
where month=7
and day=28
and year=2021
and street = 'Humphrey Street'
and description like '%CS50%'
;
-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.


select *
from interviews
where lower(transcript) like '%baker%'
and year = 2021
and month = 7
and day = 28
;

-- | id  |  name   | year | month | day |                                                                                                                                                     transcript                                                                                                                                                      |
-- +-----+---------+------+-------+-----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
-- | 161 | Ruth    | 2021 | 7     | 28  | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
select *
from bakery_security_logs
where year = 2021
and month=7
and day=28
and hour=10
and activity = 'exit'
;
-- +-----+------+-------+-----+------+--------+----------+---------------+
-- | id  | year | month | day | hour | minute | activity | license_plate |
-- +-----+------+-------+-----+------+--------+----------+---------------+
-- | 260 | 2021 | 7     | 28  | 10   | 16     | exit     | 5P2BI95       |
-- | 261 | 2021 | 7     | 28  | 10   | 18     | exit     | 94KL13X       |
-- | 262 | 2021 | 7     | 28  | 10   | 18     | exit     | 6P58WS2       |
-- | 263 | 2021 | 7     | 28  | 10   | 19     | exit     | 4328GD8       |
-- | 264 | 2021 | 7     | 28  | 10   | 20     | exit     | G412CB7       |
-- | 265 | 2021 | 7     | 28  | 10   | 21     | exit     | L93JTIZ       |
-- | 266 | 2021 | 7     | 28  | 10   | 23     | exit     | 322W7JE       |
-- | 267 | 2021 | 7     | 28  | 10   | 23     | exit     | 0NTHK55       |
-- | 268 | 2021 | 7     | 28  | 10   | 35     | exit     | 1106N58       |

-- | 162 | Eugene  | 2021 | 7     | 28  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
select *
from atm_transactions
where atm_location = 'Leggett Street'
and year = 2021
and month = 7
and day = 28
and transaction_type = 'withdraw'
;
-- +-----+----------------+------+-------+-----+----------------+------------------+--------+
-- | id  | account_number | year | month | day |  atm_location  | transaction_type | amount |
-- +-----+----------------+------+-------+-----+----------------+------------------+--------+
-- | 246 | 28500762       | 2021 | 7     | 28  | Leggett Street | withdraw         | 48     |
-- | 264 | 28296815       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     |
-- | 266 | 76054385       | 2021 | 7     | 28  | Leggett Street | withdraw         | 60     |
-- | 267 | 49610011       | 2021 | 7     | 28  | Leggett Street | withdraw         | 50     |
-- | 269 | 16153065       | 2021 | 7     | 28  | Leggett Street | withdraw         | 80     |
-- | 288 | 25506511       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     |
-- | 313 | 81061156       | 2021 | 7     | 28  | Leggett Street | withdraw         | 30     |
-- | 336 | 26013199       | 2021 | 7     | 28  | Leggett Street | withdraw         | 35     |
-- +-----+----------------+------+-------+-----+----------------+------------------+--------+

-- | 163 | Raymond | 2021 | 7     | 28  | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |
select *
from airports
where lower(full_name) like '%fiftyville%'
;
-- +----+--------------+-----------------------------+------------+
-- | id | abbreviation |          full_name          |    city    |
-- +----+--------------+-----------------------------+------------+
-- | 8  | CSF          | Fiftyville Regional Airport | Fiftyville |
-- +----+--------------+-----------------------------+------------+

select f.id as flight_id, a.full_name, a.city, f.hour, f.minute
-- select *
from flights as f
join airports as a on f.destination_airport_id = a.id
where year = 2021
and month = 7
and day = 29
and origin_airport_id = 8
and hour = 8
-- order by hour, minute
;

-- +-----------+-------------------+---------------+------+--------+
-- | flight_id |     full_name     |     city      | hour | minute |
-- +-----------+-------------------+---------------+------+--------+
-- | 36        | LaGuardia Airport | New York City | 8    | 20     |
-- +-----------+-------------------+---------------+------+--------+

with t_license as (
    select license_plate
from bakery_security_logs
where year = 2021
and month=7
and day=28
and hour=10
and minute < 30
and activity = 'exit'),
t_trans as (
 select account_number
from atm_transactions
where atm_location = 'Leggett Street'
and year = 2021
and month = 7
and day = 28
and transaction_type = 'withdraw'
),
t_calls as (
    select caller, receiver, duration, pp1.name as caller_name, pp2.name as receiver_name
from phone_calls pc
join people pp1 on pc.caller=pp1.phone_number
join people pp2 on pc.receiver=pp2.phone_number
where year = 2021
and month = 7
and day = 28
and duration < 60
)
select ps.seat, pp.*, c.duration as call_duration, c.receiver_name as call_receiver_name
from passengers ps
join people pp on ps.passport_number = pp.passport_number
join bank_accounts b on b.person_id = pp.id
join t_calls c on pp.phone_number = c.caller
where flight_id = 36
and license_plate in (select license_plate from t_license)
and account_number in (select account_number from t_trans)
;
-- +-----------+-----------------+------+--------+--------+----------------+-----------------+---------------+
-- | flight_id | passport_number | seat |   id   |  name  |  phone_number  | passport_number | license_plate |
-- +-----------+-----------------+------+--------+--------+----------------+-----------------+---------------+
-- | 36        | 1695452385      | 3B   | 398010 | Sofia  | (130) 555-0289 | 1695452385      | G412CB7       |
-- | 36        | 5773159633      | 4A   | 686048 | Bruce  | (367) 555-5533 | 5773159633      | 94KL13X       |
-- | 36        | 8294398571      | 6C   | 560886 | Kelsey | (499) 555-9472 | 8294398571      | 0NTHK55       |
-- | 36        | 1988161715      | 6D   | 449774 | Taylor | (286) 555-6063 | 1988161715      | 1106N58       |
-- | 36        | 8496433585      | 7B   | 467400 | Luca   | (389) 555-5198 | 8496433585      | 4328GD8       |
-- +-----------+-----------------+------+--------+--------+----------------+-----------------+---------------+


select caller, receiver, duration, pp1.name as caller_name, pp2.name as receiver_name
from phone_calls pc
join people pp1 on pc.caller=pp1.phone_number
join people pp2 on pc.receiver=pp2.phone_number
where year = 2021
and month = 7
and day = 28
and duration < 60
order by duration
;
-- +----------------+----------------+----------+-------------+---------------+
-- |     caller     |    receiver    | duration | caller_name | receiver_name |
-- +----------------+----------------+----------+-------------+---------------+
-- | (499) 555-9472 | (892) 555-8872 | 36       | Kelsey      | Larry         |
-- | (031) 555-6622 | (910) 555-3251 | 38       | Carina      | Jacqueline    |
-- | (286) 555-6063 | (676) 555-6554 | 43       | Taylor      | James         |
-- | (367) 555-5533 | (375) 555-8161 | 45       | Bruce       | Robin         |
-- | (770) 555-1861 | (725) 555-3243 | 49       | Diana       | Philip        |
-- | (499) 555-9472 | (717) 555-1342 | 50       | Kelsey      | Melissa       |
-- | (130) 555-0289 | (996) 555-8899 | 51       | Sofia       | Jack          |
-- | (338) 555-6650 | (704) 555-2131 | 54       | Benista     | Anna          |
-- | (826) 555-1652 | (066) 555-9701 | 55       | Kenny       | Doris         |
-- +----------------+----------------+----------+-------------+---------------+


with t_calls as (
select caller as caller_phone_number, receiver as receiver_phone_number, duration
from phone_calls
where year = 2021
and month = 7
and day = 28
and duration < 60
)
select *
from passengers ps
left join people pp on ps.passport_number = pp.passport_number
where flight_id = 36
and (phone_number in (select caller_phone_number from t_calls)
or phone_number in (select receiver_phone_number from t_calls))
;

with t_calls as (
select caller as caller_phone_number, receiver as receiver_phone_number, duration
from phone_calls
where year = 2021
and month = 7
and day = 28
and duration < 60
),
t_pass as (
select seat, name, phone_number, license_plate
from passengers ps
join people pp on ps.passport_number = pp.passport_number
where flight_id = 36
),
t_plate as (
select license_plate
from bakery_security_logs
where year = 2021
and month=7
and day=28
and hour=10
and activity = 'exit'
),
t_ppl as (
select seat, name, phone_number, license_plate
from t_pass
where license_plate in (select * from t_plate)
)
select *
from t_calls
left join t_ppl on t_calls.caller_phone_number = t_ppl.phone_number
;
-- select name, license_plate
-- from t_calls
-- join t_ppl on t_calls.caller_phone_number = t_ppl.phone_number
-- intersect
select name, license_plate
from t_calls
join t_ppl on t_calls.receiver_phone_number = t_ppl.phone_number
;