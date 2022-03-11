SELECT COUNT(*) as CONTAGEM
FROM(
    SELECT      DISTINCT (C_CUSTKEY)
    FROM        CUSTOMER
    EXCEPT
    SELECT      DISTINCT (C_CUSTKEY)
    FROM        CUSTOMER
    INNER JOIN  ORDERS ON 
                C_CUSTKEY = O_CUSTKEY
    WHERE       O_COMMENT LIKE "%special request%"
);