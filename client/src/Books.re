include Book;

let book1 = { title: "Book 1" };
let book2 = { title: "Book 2" };
let book3 = { title: "Book 3" };
let books = [book1, book2, book3];

[@react.component]
let make = () => {
  <div>
  {
    books
      |> List.map(book => <Book title=book.title/>)
      |> Array.of_list
      |> ReasonReact.array
  }
  </div>
};
