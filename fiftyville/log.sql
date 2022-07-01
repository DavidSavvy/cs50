-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Returns description of crime and mentions bakery as well as three witnesses
SELECT id, description FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28 AND street = "Humphrey Street";

--Returns various transcripts WITH KEY INFORMATION:
--Thief withdrew ATM money on Leggett Street
--Theif got into car at bakery parking lot within 10 minutes of the theft
--Theif made a call and said they were taking the earliest flight next morning, asked the other person to purchase the ticket (accomplice)
SELECT transcript FROM interviews WHERE year = 2021 AND month = 7 AND day = 28;

--Returns license plate and allows me to see people who left the parking lot within the time the interviewee mentioned
SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25 AND activity = "exit";

--Returns participants in calls under a minute long like the interviewee mentioned
SELECT caller, receiver, duration FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60;

--Returns account numbers that withdrew from Leggett Street as interviewee mentioned
SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw";

SELECT name
  FROM people
       JOIN bank_accounts
         ON people.id = bank_accounts.person_id

       JOIN phone_calls
         ON people.phone_number = phone_calls.caller
 WHERE bank_accounts.account_number IN
       (SELECT account_number
          FROM atm_transactions
         WHERE year = 2021
           AND month = 7
           AND day = 28
           AND atm_location = "Leggett Street"
           AND transaction_type = "withdraw")
   AND people.phone_number IN
       (SELECT caller
          FROM phone_calls
         WHERE year = 2021
           AND month = 7
           AND day = 28
           AND duration < 60)
   AND people.license_plate IN
       (SELECT license_plate
          FROM bakery_security_logs
         WHERE year = 2021
           AND month = 7
           AND day = 28
           AND hour = 10
           AND minute > 15
           AND minute < 25
           AND activity = "exit");