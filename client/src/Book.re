type book = { title: string, tags: list(string) };

module Tag = {
  [@react.component]
  let make = (~tag) => {
    <li>{ReasonReact.string(tag)}</li>
  }
}

module TagList = {
  [@react.component]
  let make = (~tags) => {
    <ul>
    {
      tags
      |> List.map(tag => <Tag tag=tag/>)
      |> Array.of_list
      |> ReasonReact.array
    }
    </ul>
  }
}

[@react.component]
let make = (~title, ~tags) => {
  <div>
    <span>{ReasonReact.string(title)}</span>
    <TagList tags=tags/>
  </div>
};

