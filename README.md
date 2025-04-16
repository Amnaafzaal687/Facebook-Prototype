# 👥 Console-Based Social Network Application

This is a console-based simulation of a social networking platform. The application mimics features like friend lists, page likes, posting, commenting, liking posts, sharing memories, and viewing timelines – all through structured C++ classes with dynamic memory allocation and without any user input during runtime.

---

## 📌 Project Overview

**Evaluation**: Based on implementation of functionalities, use of best practices, dynamic memory handling, and adherence to design

---

## 🧩 Features

- User profile with:
  - Unique ID & name
  - Friend list (up to 10)
  - Liked pages (up to 10)
- Pages with:
  - Unique ID
  - Title
  - Timeline (posts)
  - Like count
- Posts with:
  - Unique ID
  - Description, date, number of likes
  - Comments (up to 10)
  - Optional activity (e.g., feeling happy, celebrating, making memories)
  - Memory posts (point to original posts)
- Commenting by users or pages
- Simulated system date

---

## 🛠 Functionality Implemented

| Command                           | Description                                         |
| --------------------------------- | --------------------------------------------------- |
| `Set current system date`         | Initialize the system date for comparison           |
| `Set current user`                | Sets current user context for operations            |
| `View Friend List`                | Displays friend list of current user                |
| `View Liked Pages`                | Lists pages liked by current user                   |
| `View Home`                       | Shows posts from friends & liked pages (past 24h)   |
| `View Timeline`                   | Displays all posts made by current user             |
| `LikePost(postID)`                | Adds like to a post                                 |
| `ViewLikedList(postID)`           | Shows users/pages who liked the post                |
| `PostComment(postID, comment)`    | Adds comment to a post                              |
| `ViewPost(postID)`                | Shows post along with comments                      |
| `SeeYourMemories()`               | Shows memory posts from same date in previous years |
| `ShareMemory(postID, memoryText)` | Shares a post as a memory                           |
| `ViewPage(pageID)`                | Displays all posts made by a specific page          |

---

## 📐 Object-Oriented Design (Overview)

> 💡 Class Diagram submitted separately on paper

- **User**
  - ID, Name, Friends[10], LikedPages[10], Posts
- **Page**
  - ID, Title, Posts[], LikedByCount
- **Post**
  - ID, Text, Date, Likes[], Comments[], Activity, Pointer to Original (for memory)
- **Comment**
  - Text, Author (User/Page)
- **Activity**
  - Type (Feeling, Making, etc.), Value
- **SocialNetworkApp**
  - CurrentUser, SystemDate, Main Data Store
  - `Run()` function to simulate the sample run

---

## ⚙️ Implementation Notes

- **No runtime input** – All actions are hardcoded inside the `Run()` function
- **Memory Management** – Dynamic allocation used for all object arrays (friends, posts, comments)
- **Null Pointers** – Used for empty dynamic arrays instead of default empty lists
- **Double Pointers** – Used where arrays of objects are maintained (e.g., posts of a user/page)
- **Best Practices** – No global variables/functions, proper class encapsulation, readable function and variable naming

---

## 🧪 Sample Execution (Hardcoded)

All sample outputs (like setting current user, viewing friend list, liking a post, etc.) are hardcoded within the `SocialNetworkApp::Run()` method as per project requirements.

This includes simulating:

- Home view posts
- Timeline activities
- Comments on posts
- Memory sharing
- Viewing pages

---
