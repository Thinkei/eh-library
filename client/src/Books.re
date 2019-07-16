include Book;

let book1 = {title: "ReasonML", tags: ["frontend", "ocaml"]};
let book2 = {title: "Ruby on Rails", tags: ["backend", "ruby", "rails"]};
let book3 = {title: "Rust", tags: ["backend", "ownership"]};
let books = [book1, book2, book3];

[@react.component]
let make = () => {
  <div>
    {books
     |> List.map(book => <Book title={book.title} tags={book.tags} />)
     |> Array.of_list
     |> ReasonReact.array}
  </div>;
};
