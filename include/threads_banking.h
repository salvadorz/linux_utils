/*
 * @threads_banking.h
 *
 * @version: 1.0
 * @Author:  Salvador Z
 * @brief:   threads_banking
 */

#ifndef threads_banking_H_
#define threads_banking_H_

#include <pthread.h>
#include <stdbool.h>

/**
 * The type of locking to use for withdrawls
 */
typedef enum withdraw_locking {
  ACCOUNT_LOCKING_NONE  = 0,  // unsafe implementation (demo purposes)
  ACCOUNT_LOCKING_MUTEX = 1,  // use a lock and unlock mutex approach
  ACCOUNT_LOCKING_MAX   = 2,  // Max number of Locking types defined
} withdraw_locking_t;

/**
 * A structure representing a fictional bank account for withdrawls
 */
typedef struct account {
  /**
   * The current balance of the account
   */
  int current_balance;
  /**
   * The total of approved withdrawls on the account
   */
  unsigned int withdrawl_total;

  /**
   * The mutex used to lock this account when manipulating values, for thread
   * safety
   */
  pthread_mutex_t mutex;

  /**
   * The type of locking we use when interacting with the account
   * (for demonstration purposes)
   */
  withdraw_locking_t locktype;
} account_t;


bool withdraw_account_init(account_t *account,
                           unsigned int starting_balance,
                           withdraw_locking_t locktype);

/**
 * @brief Perform withdrawals from specified account
 *
 * @param account to perform withdrawals
 * @param withdraw_request amount to withdraw
 */
void do_withdrawls(account_t *account, unsigned int withdraw_request);

/**
 * @brief Disburse amount money
 *
 * @param amount to be disbursed
 */
void disburse_money(unsigned int amount);

#endif // threads_banking_H_