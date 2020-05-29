#!/bin/bash

# echo "TEST #1 /unsubscribe"
# (
#     echo -ne "START_COMM\r\n/login\r\nssu\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/subscribe\r\n76f8d709-0bf8-4681-a55c-f249351a0120\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/login\r\nchase\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/unsubscribe\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/unsubscribe\r\nfezfzefze\r\nioifjezifj\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/unsubscribe\r\nifjeofjfzeiof\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/subscribe\r\n76f8d709-0bf8-4681-a55c-f249351a0120\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/unsubscribe\r\n76f8d709-0bf8-4681-a55c-f249351a0120\r\nEND_COMM\r\n"
# ) | nc 127.0.0.1 4242

# echo ""
# echo "TEST #2 /list"
# (
#     echo -ne "START_COMM\r\n/list\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/login\r\nchase\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/list\r\nehfzeiohfzeio\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/list\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/use\r\n76f8d709-0bf8-4681-a55c-f249351a0120\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/list\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/use\r\n76f8d709-0bf8-4681-a55c-f249351a0120\r\ne6715971-e368-49f7-b796-93e0c4eead49\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/list\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/use\r\n76f8d709-0bf8-4681-a55c-f249351a0120\r\ne6715971-e368-49f7-b796-93e0c4eead49\r\n66726590-0265-4cdd-b5c6-4f060698dd65\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/list\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/logout\r\nEND_COMM\r\n"
# ) | nc 127.0.0.1 4242

# echo ""
# echo "TEST #3 Thread"
# (
#     echo -ne "START_COMM\r\n/login\r\nmoulinette\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/create\r\nmouli team\r\nmouli team desc\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/use\r\n76f8d709-0bf8-4681-a55c-f249351a0120\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/create\r\nmouli channel\r\nmouli channel desc\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/use\r\n76f8d709-0bf8-4681-a55c-f249351a0120\r\ne6715971-e368-49f7-b796-93e0c4eead49\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/create\r\nmol\r\nmtd\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/use\r\n76f8d709-0bf8-4681-a55c-f249351a0120\r\ne6715971-e368-49f7-b796-93e0c4eead49\r\n66726590-0265-4cdd-b5c6-4f060698dd65\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/create\r\nmouli comment\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/logout\r\nEND_COMM\r\n"
# ) | nc 127.0.0.1 4242

# echo ""
# echo "TEST #4 /send"
# (
#     echo -ne "START_COMM\r\n/send\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/login\r\nmoulinette\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/send\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/send\r\nefijzefio\r\nfzeojfzeiof\r\nezofzeiofzejif\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/send\r\nefijzefio\r\nfzeojfzeiof\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/send\r\nadb8030c-67aa-41a3-bb3a-0ea0b4641dc6\r\nMoulinette sending message to chase\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/logout\r\nEND_COMM\r\n"
# ) | nc 127.0.0.1 4242

# echo ""
# echo "TEST #4 /login /logout"
# (
#     echo -ne "START_COMM\r\n/login\r\nmoulinette\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/logout\r\nEND_COMM\r\n"
# ) | ./myteams_cli 127.0.0.1 4242

# echo ""
# echo "TEST #7 create thread"
# (
#     echo -ne "START_COMM\r\n/login\r\nchase\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/use\r\n76f8d709-0bf8-4681-a55c-f249351a0120\r\ne6715971-e368-49f7-b796-93e0c4eead49\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/create\r\ntester thread\r\ntester init\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/logout\r\nEND_COMM\r\n"
# ) | nc 127.0.0.1 4242


# echo ""
# echo "TEST #7 create comment"
# (
#     echo -ne "START_COMM\r\n/login\r\nchase\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/use\r\n76f8d709-0bf8-4681-a55c-f249351a0120\r\ne6715971-e368-49f7-b796-93e0c4eead49\r\n45ccfaa2-46d5-45c2-a380-51062e1a4506\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/create\r\ntime comment\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/create\r\nanother comment\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/create\r\nyet another comment\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/logout\r\nEND_COMM\r\n"
# ) | nc 127.0.0.1 4242

# echo ""
# echo "TEST #2 /list"
# (
#     echo -ne "START_COMM\r\n/login\r\nchase\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/list\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/use\r\n76f8d709-0bf8-4681-a55c-f249351a0120\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/list\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/use\r\n76f8d709-0bf8-4681-a55c-f249351a0120\r\ne6715971-e368-49f7-b796-93e0c4eead49\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/list\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/use\r\n76f8d709-0bf8-4681-a55c-f249351a0120\r\ne6715971-e368-49f7-b796-93e0c4eead49\r\n66726590-0265-4cdd-b5c6-4f060698dd65\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/list\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/logout\r\nEND_COMM\r\n"
# ) | nc 127.0.0.1 4242

# echo ""
# echo "TEST #4 /send"
# (
#     echo -ne "START_COMM\r\n/login\r\nmoulinette\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/send\r\nadb8030c-67aa-41a3-bb3a-0ea0b4641dc6\r\nMoulinette sending message to chase\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/logout\r\nEND_COMM\r\n"
# ) | nc 127.0.0.1 4242

# echo "TEST #4 /users"
# (
#     echo -ne "START_COMM\r\n/login\r\nmoulinette\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/users\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/logout\r\nEND_COMM\r\n"
# ) | nc 127.0.0.1 4242

# echo "TEST #4 /user"
# (
#     echo -ne "START_COMM\r\n/login\r\nmoulinette\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/user\r\nee764899-3402-4db7-8596-21f386be9cbc\r\nEND_COMM\r\n"
#     sleep 0.05
#     echo -ne "START_COMM\r\n/logout\r\nEND_COMM\r\n"
# ) | nc 127.0.0.1 4242

echo "TEST #4 /messages"
(
    echo -ne "START_COMM\r\n/login\r\nmoulinette\r\nEND_COMM\r\n"
    sleep 0.05
    echo -ne "START_COMM\r\n/messages\r\nadb8030c-67aa-41a3-bb3a-0ea0b4641dc6\r\nEND_COMM\r\n"
    sleep 0.05
    echo -ne "START_COMM\r\n/logout\r\nEND_COMM\r\n"
) | nc 127.0.0.1 4242