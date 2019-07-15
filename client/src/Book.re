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
    <span>{ReasonReact.string(title)}</span>
    <ul>
    {
      tags
      |> List.map(tag => <Tag tag=tag/>)
      |> Array.of_list
      |> ReasonReact.array
    }
    </ul>
  </div>
};

