# LeOS Coding Style

## Files names

1. Only lower case
2. Words separated with underscore:
```
aarch64/aarch64_boot.S
```

## Preprocessor macro constants

1. Only upper case
2. Words separated with underscore:

```
#define AARCH64_CORE0_TIMER_IRQCTL (*((uint32_t *) 0x40000040))
```

## Types

1. Camel case started from upper case
2. Do not typedef transparent structures
3. Members of structre should be named in camel case started from lower case

```
struct Task {
        void *sp;
        void *stackStart;
        uint32_t pid;
        uint32_t stackSize;
        uint32_t lock;
        uint32_t counter;
        uint32_t cycles;
        int32_t priority;
        uint32_t state;
        char name[CONFIG_TASK_MAX_NAME_LEN + 1];
        struct Task *next;
};
```

## Constants and variables

1. Global constants and variablesmust be prefixed with `g_`
2. Module (static) constants and variable must be prefixed `m_`
3. Camel case

```
static struct Task *m_currentTask = NULL;
```

## Functions

1. Camel case
2. Prefix separated from function identifier by underscore
3. Static functions may have no prefix
4. Prefix always starts from capital letter
5. Function identifier always starts from lower case verb

```
unsigned int
AArch64_getEL(void);

static struct Task *
scheduleNext(void);
```

## Namespaces and prefixes

1. Due to C has no native namespaces, prefixes should always be used
2. Prefix should match with file name

```
/* file : task.h */

void
Task_initSheduler(void);

```
