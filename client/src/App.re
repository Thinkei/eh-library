open Ehd;
open Route;

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
      ~border="0.5px solid #d8d8d8",
      ~minHeight="100vh",
      (),
    );
  let sider = ReactDOMRe.Style.make(~lineHeight="120px", ());
  let content =
    ReactDOMRe.Style.make(~minHeight="120px", ~lineHeight="120px", ());
  let footer = ReactDOMRe.Style.make(~textAlign="right", ());
};

[@react.component]
let make = () =>
  <Layout style=Styles.layoutWrapper>
    <Sider style=Styles.sider trigger=ReasonReact.null collapsible=true>
      <Link
        style={ReactDOMRe.Style.make(~color="white", ())}
        route=Config.MyProfile>
        {ReasonReact.string("My Profile")}
      </Link>
      <br />
      <Link
        style={ReactDOMRe.Style.make(~color="white", ())} route=Config.Books>
        {ReasonReact.string("Books")}
      </Link>
      <br />
      <Link
        style={ReactDOMRe.Style.make(~color="white", ())}
        route=Config.Shipper>
        {ReasonReact.string("Shipper")}
      </Link>
    </Sider>
    <Layout>
      <Header>
        <Typography.Title level=1>
          {str("EH Book Management")}
        </Typography.Title>
      </Header>
      <Content style=Styles.content>
        <AppRouter>
          {currentRoute =>
             Route.Config.(
               switch (currentRoute) {
               | Home => <Books />
               | Books => <Books />
               | MyProfile => <MyProfile />
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
    </Layout>
  </Layout>;
