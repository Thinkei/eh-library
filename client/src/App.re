[%bs.raw {|require("./styles/App.css")|}];

open Ehd;

module AppRouter = Router.Create(Route.Config);

let str = ReasonReact.string;

module Sider = Layout.Sider;
module Header = Layout.Header;
module Content = Layout.Content;
module Footer = Layout.Footer;

module Styles = {
  let layoutWrapper =
    ReactDOMRe.Style.make(
      ~fontSize="14px",
      ~textAlign="center",
      // ~border="0.5px solid #d8d8d8",
      ~minHeight="100vh",
      (),
    );
  let sider = ReactDOMRe.Style.make(~lineHeight="120px", ());
  let content =
    ReactDOMRe.Style.make(~minHeight="120px", ~lineHeight="120px", ());
  let footer = ReactDOMRe.Style.make(~textAlign="right", ());
  let header =
    ReactDOMRe.Style.make(~position="fixed", ~zIndex="1", ~width="100%", ());
};

[@react.component]
let make = () =>
  <Layout style=Styles.layoutWrapper>
    <Content style=Styles.content>
      <AppRouter>
        {currentRoute =>
           Route.Config.(
             switch (currentRoute) {
             | Home => <LandingPage.Index />
             | Books => <NewBooks />
             | MyProfile => <MyProfile firstName="Hieu" lastName=None />
             | NewBook => <NewBook />
             | Shipper => <Shipper />
             | NotFound => <div> {ReasonReact.string("Not Found")} </div>
             }
           )}
      </AppRouter>
    </Content>
    <Footer style=Styles.footer>
      {str({js| Implemented by 🐪 EH ReasonML adventurers group |js})}
    </Footer>
  </Layout>;
