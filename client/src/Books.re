type book = {
  title: string,
};

type books = [book];

let books = [{title: "ReasonML"}];

[@react.component]
let make = (~books) => {
  books
  |> List.map(book => <Book/>)
  |> Array.of_list
  |> ReasonReact.array
};
