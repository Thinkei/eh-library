type book = { title: string, tags: list(string) };

module Tag = {
  [@react.component]
  let make = (~tag) => {
    <li>{ReasonReact.string(tag)}</li>
  }
}

[@react.component]
let make = (~title, ~tags) => {
  <div>
    <div>{ReasonReact.string(title)}</div>
    <ul>
    {
      tags
      |> List.map(tag => <Tag key=tag tag=tag/>)
      |> Array.of_list
      |> ReasonReact.array
    }
    </ul>
  </div>
};

